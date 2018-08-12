#pragma once

#include "Core.hpp"
#include "Core_VectorMap.hpp"
#include "Core_BitVector.hpp"
#include "Core_StringHash.hpp"
#include "Core_AlignedStorage.hpp"
#include "Core_ResourceHandle.hpp"
#include "Core_Algorithm.hpp"
#include "Core_Optional.hpp"

namespace Alba
{
	namespace Core
	{
		union ResourceIdInternal
		{
			// Note: Size must add up to 64 bits
			struct Fields
			{
				uint32	myIndex		: 32;
				uint32  myNameHash	: 32;
			};

			Fields myFields;
			uint64 myValue;
		};

		// Ensure fields fit inside myValue
		static_assert(sizeof(ResourceIdInternal::myFields) == sizeof(ResourceIdInternal::myValue));

		//-----------------------------------------------------------------------------------------
		// Name	:	ResourceRepository
		// Desc	:	Provides reference-counted storage/access to a specific resource type
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		class ResourceRepository
		{
			public:

				//=================================================================================
				// Public Types
				//=================================================================================
				typedef ResourceHandle<TResourceType, TDerived>			Handle;
				friend class ResourceHandle<TResourceType, TDerived>;

				//=================================================================================
				// Public Constructors/Destructors
				//=================================================================================
				~ResourceRepository();

				//=================================================================================
				// Public Methods
				//=================================================================================
				inline Handle				GetResource(NoCaseStringHash32 aResourceNameId);
				inline Handle				GetOrCreateResource(const Core::StringView& aResourceName, NoCaseStringHash32 aResourceNameId);

				inline bool					HasResource(NoCaseStringHash32 aResourceNameId) const;

			protected:

				//=================================================================================
				// Protected Constructors
				//=================================================================================
				ResourceRepository(uint32 aReserveSize);

				//=================================================================================
				// Protected Constructors
				//=================================================================================
				inline Handle				CreateResource(const Core::StringView& aResourceName, NoCaseStringHash32 aResourceNameId);
				inline void					DestroyResource(NoCaseStringHash32 aResourceNameId);
				inline void					DestroyResource(Handle aHandle);
			
			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				inline const TResourceType*	GetResourcePtr(Handle aHandle) const;
				inline TResourceType*		GetResourcePtrMutable(Handle aHandle);
				inline void					DestroyResourceInternal(size_t anIndex);

				inline Core::Optional<size_t> HandleToIndex(Handle aHandle) const
				{
					const ResourceId<TResourceType> id = aHandle.GetId();
					const uint64 idValue = id.GetValue();

					// Need to memcpy because it's undefined behavior to access more than 
					// one field of the same union
					ResourceIdInternal idFields;
					std::memcpy(&idFields, &idValue, sizeof(idFields));

					return idFields.myIndex;
				}

				//=================================================================================
				// Private Data
				//=================================================================================
				Vector<TResourceType>					myResources;

				VectorMap<NoCaseStringHash32, uint32>	myNameIdHashToIndex;
				BitVector<uint64>						myFreeIndices;

				Mutex									myModifyFreeIndicesMutex;
				ReadWriteMutex							myModifyNameIdHashToIndex;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		/*inline*/ ResourceRepository<TDerived, TResourceType>::ResourceRepository(uint32 aReserveSize)
		{
			myResources.resize(aReserveSize);
			myFreeIndices.set(aReserveSize, true);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		/*inline*/ ResourceRepository<TDerived, TResourceType>::~ResourceRepository()
		{
			myResources.clear();
			myFreeIndices.clear();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		typename ResourceRepository<TDerived, TResourceType>::Handle ResourceRepository<TDerived, TResourceType>::GetResource(NoCaseStringHash32 aResourceNameId)
		{
			Core::ScopedReaderMutexLock lock(myModifyNameIdHashToIndex);

			auto itr = myNameIdHashToIndex.find(aResourceNameId);
			if (itr != myNameIdHashToIndex.end())
			{
				ALBA_ASSERT(myResources.size() > itr->second);
				const TResourceType* resource = myResources[itr->second];

				return Handle(resource->GetId(), static_cast<TDerived&>(*this));
			}

			return Handle();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		typename ResourceRepository<TDerived, TResourceType>::Handle ResourceRepository<TDerived, TResourceType>::GetOrCreateResource(const Core::StringView& aResourceName, NoCaseStringHash32 aResourceNameId)
		{
			Core::ScopedReaderMutexLock lock(myModifyNameIdHashToIndex);

			auto itr = myNameIdHashToIndex.find(aResourceNameId);
			if (itr != myNameIdHashToIndex.end())
			{
				ALBA_ASSERT(myResources.size() > itr->second);
				const TResourceType* resource = &myResources[itr->second];

				return Handle(resource->GetId(), static_cast<TDerived&>(*this));
			}
			else
			{
				return CreateResource(aResourceName, aResourceNameId);
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		/*inline*/ bool ResourceRepository<TDerived, TResourceType>::HasResource(NoCaseStringHash32 aResourceNameId) const
		{
			Core::ScopedReaderMutexLock lock(myModifyNameIdHashToIndex);

			return myNameIdHashToIndex.find(aResourceNameId) != myResources.end();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		/*inline*/ typename ResourceRepository<TDerived, TResourceType>::Handle ResourceRepository<TDerived, TResourceType>::CreateResource(const Core::StringView& aResourceName, NoCaseStringHash32 aResourceNameId)
		{
			uint64 index = 0;

			{
				Core::ScopedMutexLock lock(myModifyFreeIndicesMutex);

				// Find first free index
				uint64 baseIndex = 0;

				for (uint64 entry : myFreeIndices.get_container())
				{
					index = index & (index - 1);

					if (index != 0)
					{
						index += baseIndex;			
						break;
					}

					baseIndex += (sizeof(entry) * 8);
				}

				// If index is invalid then bail
				if (index >= myFreeIndices.size() || !myFreeIndices[index])
				{
					return Handle();
				}

				myFreeIndices[index] = false;
			}
			
			// Generate ID
			ResourceIdInternal idFields;
			idFields.myFields.myIndex = index;
			idFields.myFields.myNameHash = aResourceNameId.GetHash();

			ResourceIdInternal idValue;
			std::memcpy(&idValue, &idFields, sizeof(idValue));

			const ResourceId<TResourceType> id(idValue.myValue);
			
			// Set resource
			myResources[index] = TResourceType(aResourceNameId, id);
			myResources[index].SetResourceName(aResourceName);

			// Set name lookup
			{
				Core::ScopedWriterMutexLock lock(myModifyNameIdHashToIndex);
				myNameIdHashToIndex[aResourceNameId] = static_cast<uint32>(index);
			}

			return Handle(id, static_cast<TDerived&>(*this));
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		/*inline*/ void ResourceRepository<TDerived, TResourceType>::DestroyResource(NoCaseStringHash32 aResourceNameId)
		{
			const Handle resourceHandle = GetResource(aResourceNameId);

			auto itr = myNameIdHashToIndex.find(aResourceNameId);
			if (itr != myNameIdHashToIndex.end())
			{
				DestroyResourceInternal(itr->second);
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		/*inline*/ void ResourceRepository<TDerived, TResourceType>::DestroyResource(Handle aHandle)
		{
			const Core::Optional<size_t> index = HandleToIndex(aHandle);

			if (!index.has_value())
			{
				return;
			}

			if (index.get() >= myResources.size())
			{
				return;
			}

			if (myResources[index.get()].GetId() != aHandle.GetId())
			{
				return;
			}

			DestroyResourceInternal(index.get());
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		/*inline*/ void	ResourceRepository<TDerived, TResourceType>::DestroyResourceInternal(size_t anIndex)
		{
			{
				Core::ScopedWriterMutexLock(myModifyNameIdHashToIndex);
	
				auto itr = Algorithm::find_if(myNameIdHashToIndex.begin(), myNameIdHashToIndex.end(), [&anIndex](const auto& entry)
				{
					return entry.second == anIndex;
				});

				if (itr != myNameIdHashToIndex.end())
				{
					myNameIdHashToIndex.erase(itr);
				}
			}

			{
				Core::ScopedMutexLock lock(myModifyFreeIndicesMutex);
				
				myResources[index] = TResourceType();
				myFreeIndices[anIndex] = true;
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		const TResourceType* ResourceRepository<TDerived, TResourceType>::GetResourcePtr(typename ResourceRepository<TDerived, TResourceType>::Handle aResourceHandle) const
		{
			const Core::Optional<size_t> index = HandleToIndex(aHandle);

			if (!index.has_value())
			{
				return nullptr;
			}

			if (index.get() >= myResources.size())
			{
				return nullptr;
			}

			if (myResources[index.get()].GetId() != aHandle.GetId())
			{
				return nullptr;
			}

			return &(myResources[index.get()]);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		TResourceType* ResourceRepository<TDerived, TResourceType>::GetResourcePtrMutable(typename ResourceRepository<TDerived, TResourceType>::Handle aResourceHandle)
		{
			const Core::Optional<size_t> index = HandleToIndex(aHandle);

			if (!index.has_value())
			{
				return nullptr;
			}

			if (index.get() >= myResources.size())
			{
				return nullptr;
			}

			if (myResources[index.get()].GetId() != aHandle.GetId())
			{
				return nullptr;
			}

			return &(myResources[index.get()]);
		}
	}
}