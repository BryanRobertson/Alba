#pragma once

#include "Core.hpp"
#include "Core_VectorMap.hpp"
#include "Core_BitVector.hpp"
#include "Core_StringHash.hpp"
#include "Core_AlignedStorage.hpp"
#include "Core_ResourceHandle.hpp"

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

			// Ensure fields fit inside myValue
			static_assert(sizeof(myFields) == sizeof(myValue));
		};

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
				typedef ResourceHandle<TResourceType, ResourceRepository<TDerived, TResourceType> > Handle;
				friend class ResourceHandle<TResourceType, ResourceRepository<TDerived, TResourceType> >;

				//=================================================================================
				// Public Constructors/Destructors
				//=================================================================================
				~ResourceRepository();

				//=================================================================================
				// Public Methods
				//=================================================================================
				inline Handle				GetResource(NoCaseStringHash32 aResourceNameId) const;
				inline bool					HasResource(NoCaseStringHash32 aResourceNameId) const;

			protected:

				//=================================================================================
				// Protected Constructors
				//=================================================================================
				ResourceRepository(uint32 aReserveSize);

				//=================================================================================
				// Protected Constructors
				//=================================================================================
				inline Handle				CreateResource(NoCaseStringHash32 aResourceNameId);
				inline void					DestroyResource(NoCaseStringHash32 aResourceNameId);
				inline void					DestroyResource(Handle aHandle);
			
			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				inline const TResourceType*	GetResourcePtr(Handle aHandle) const;
				inline TResourceType*		GetResourcePtrMutable(Handle aHandle);

				inline void					DestroyResourceInternal(size_t anIndex);

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
		ResourceRepository<TDerived, TResourceType>::Handle ResourceRepository<TDerived, TResourceType>::GetResource(NoCaseStringHash32 aResourceNameId) const
		{
			Core::ScopedReaderMutexLock lock(myModifyNameIdHashToIndex);

			auto itr = myNameIdHashToIndex.find(aResourceNameId);
			if (itr != myNameIdHashToIndex.end())
			{
				ALBA_ASSERT(myResources.size() > itr->second);
				const TResourceType* resource = myResources[itr->second];

				return resource->GetId();
			}

			return Handle();
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
		/*inline*/ ResourceRepository<TDerived, TResourceType>::Handle ResourceRepository<TDerived, TResourceType>::CreateResource(NoCaseStringHash32 aResourceNameId)
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
			std::memcpy(&idValue, *idFields, sizeof(idValue));

			const ResourceId<TResourceType> id(idValue.myValue);
			
			// Set resource
			myResources[index] = TResourceType(id);

			// Set name lookup
			{
				Core::ScopedWriterMutexLock lock(myModifyNameIdHashToIndex);
				myNameIdHashToIndex[aResourceNameId] = index;
			}

			const Handle resourceHandle(aResourceNameId, id);
			return resourceHandle;
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
			const ResourceId<TResourceType> id = aHandle.GetId();
			const uint64 idValue = id.GetValue();

			ResourceIdInternal idFields;
			std::memcpy(&idFields, &idValue, sizeof(idFields));

			if (idFields.myFields.myIndex >= myResources.size())
			{
				return;
			}

			if (myResources[idFields.myFields.myIndex].GetId() != id)
			{
				return;
			}

			DestroyResourceInternal(idFields.myFields.myIndex);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		/*inline*/ void	ResourceRepository<TDerived, TResourceType>::DestroyResourceInternal(size_t anIndex)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		const TResourceType* ResourceRepository<TDerived, TResourceType>::GetResourcePtr(ResourceRepository<TDerived, TResourceType>::Handle aResourceHandle) const
		{
			//const TResourceType* resource = myResources[itr->second];
			//resource->GetId();
			return nullptr;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		TResourceType* ResourceRepository<TDerived, TResourceType>::GetResourcePtrMutable(ResourceRepository<TDerived, TResourceType>::Handle aResourceHandle)
		{
			//const TResourceType* resource = myResources[itr->second];
			//resource->GetId();
			return nullptr;
		}
	}
}