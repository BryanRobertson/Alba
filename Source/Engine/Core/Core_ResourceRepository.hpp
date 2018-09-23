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
				uint32  myHash		: 16;
				uint32	myCounter	: 16;
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
		template <typename TResourceType>
		class ResourceRepository
		{
			public:

				friend class ResourceHandle<TResourceType>;

				//=================================================================================
				// Public Types
				//=================================================================================
				typedef ResourceHandle<TResourceType>	Handle;
				
				//=================================================================================
				// Public Constructors/Destructors
				//=================================================================================
				~ResourceRepository();

				//=================================================================================
				// Public Methods
				//=================================================================================
				inline Handle				GetResource(NoCaseStringHash32 aResourceNameId);
				inline bool					HasResource(NoCaseStringHash32 aResourceNameId) const;

				inline Handle				CreateResource();
				inline Handle				CreateResource(NoCaseStringHash32 aResourceNameId);

			protected:

				//=================================================================================
				// Protected Constructors
				//=================================================================================
				ResourceRepository(uint32 aReserveSize);

				//=================================================================================
				// Protected Constructors
				//=================================================================================
				inline void					DestroyResource(NoCaseStringHash32 aResourceNameId);
				inline void					DestroyResource(Handle aHandle);
			
			private:

				//=================================================================================
				// Protected Types
				//=================================================================================
				typedef AlignedStorage<sizeof(TResourceType), alignof(TResourceType)> StorageType;

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

					return idFields.myFields.myIndex;
				}

				//=================================================================================
				// Private Data
				//=================================================================================
				Vector<StorageType>						myResources;

				VectorMap<NoCaseStringHash32, uint32>	myNameIdHashToIndex;
				BitVector<uint64>						myFreeIndices;

				Mutex									myModifyFreeIndicesMutex;
				mutable ReadWriteMutex					myModifyNameIdHashToIndex;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TResourceType>
		/*inline*/ ResourceRepository<TResourceType>::ResourceRepository(uint32 aReserveSize)
		{
			myResources.resize(aReserveSize);
			myFreeIndices.set(aReserveSize, true);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TResourceType>
		/*inline*/ ResourceRepository<TResourceType>::~ResourceRepository()
		{
			myResources.clear();
			myFreeIndices.clear();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TResourceType>
		typename ResourceRepository<TResourceType>::Handle ResourceRepository<TResourceType>::GetResource(NoCaseStringHash32 aResourceNameId)
		{
			Core::ScopedReaderMutexLock lock(myModifyNameIdHashToIndex);

			auto itr = myNameIdHashToIndex.find(aResourceNameId);
			if (itr != myNameIdHashToIndex.end())
			{
				ALBA_ASSERT(myResources.size() > itr->second);
				const TResourceType* resource = reinterpret_cast<TResourceType*>(&myResources[itr->second]);

				return Handle(resource->GetId(), *this);
			}

			return Handle();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TResourceType>
		/*inline*/ bool ResourceRepository<TResourceType>::HasResource(NoCaseStringHash32 aResourceNameId) const
		{
			Core::ScopedReaderMutexLock lock(myModifyNameIdHashToIndex);

			return myNameIdHashToIndex.find(aResourceNameId) != myNameIdHashToIndex.end();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TResourceType>
		/*inline*/ typename ResourceRepository<TResourceType>::Handle ResourceRepository<TResourceType>::CreateResource()
		{
			return CreateResource(NoCaseStringHash32::ourInvalidHashValue);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TResourceType>
		/*inline*/ typename ResourceRepository<TResourceType>::Handle ResourceRepository<TResourceType>::CreateResource(NoCaseStringHash32 aResourceNameId)
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

			{
				static uint32 counter = 0;

				idFields.myFields.myIndex = index;
				idFields.myFields.myHash = Core::ConvertHash<NoCaseStringHash16>(aResourceNameId).GetHash();
				idFields.myFields.myUniqueId = ++counter;
			}

			ResourceIdInternal idValue;
			std::memcpy(&idValue, &idFields, sizeof(idValue));

			const ResourceId<TResourceType> id(idValue.myValue);
			
			// Set resource
			new (&myResources[index]) TResourceType(aResourceNameId, id);

			// Set name lookup
			if ( aResourceNameId.IsValid() )
			{
				Core::ScopedWriterMutexLock lock(myModifyNameIdHashToIndex);
				myNameIdHashToIndex[aResourceNameId] = static_cast<uint32>(index);
			}

			return Handle(id, *this);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TResourceType>
		/*inline*/ void ResourceRepository<TResourceType>::DestroyResource(NoCaseStringHash32 aResourceNameId)
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
		template <typename TResourceType>
		/*inline*/ void ResourceRepository<TResourceType>::DestroyResource(Handle aHandle)
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

			TResourceType* resource = reinterpret_cast<TResourceType>(myResources[index.get()]);
			if (resource->GetId() != aHandle.GetId())
			{
				return;
			}

			DestroyResourceInternal(index.get());
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TResourceType>
		/*inline*/ void	ResourceRepository<TResourceType>::DestroyResourceInternal(size_t anIndex)
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
				
				TResourceType* resource = reinterpret_cast<TResourceType>(myResources[index]);

				resource->~TResourceType();
				myFreeIndices[anIndex] = true;
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TResourceType>
		const TResourceType* ResourceRepository<TResourceType>::GetResourcePtr(typename ResourceRepository<TResourceType>::Handle aResourceHandle) const
		{
			const Core::Optional<size_t> index = HandleToIndex(aHandle);

			if (!index.has_value())
			{
				return nullptr;
			}

			const size_t indexValue = index.value();
			if (indexValue >= myResources.size())
			{
				return nullptr;
			}

			const TResourceType* resource = reinterpret_cast<TResourceType*>(&myResources[index.value()]);
			if (resource->GetId() != aHandle.GetId())
			{
				return nullptr;
			}

			return resource;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TResourceType>
		TResourceType* ResourceRepository<TResourceType>::GetResourcePtrMutable(typename ResourceRepository<TResourceType>::Handle aResourceHandle)
		{
			const Core::Optional<size_t> index = HandleToIndex(aResourceHandle);

			if (!index.has_value())
			{
				return nullptr;
			}

			const size_t indexValue = index.value();
			if (indexValue >= myResources.size())
			{
				return nullptr;
			}

			TResourceType* resource = reinterpret_cast<TResourceType*>(&myResources[index.value()]);
			if (resource->GetId() != aResourceHandle.GetId())
			{
				return nullptr;
			}

			return resource;
		}
	}
}