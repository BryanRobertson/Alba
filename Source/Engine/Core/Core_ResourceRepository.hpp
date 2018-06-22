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
		//-----------------------------------------------------------------------------------------
		// Name	:	ResourceRepository
		// Desc	:	Provides reference-counted storage/access to a specific resource type
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		class ResourceRepository
		{
			protected:

				typedef ResourceHandle<TResourceType, ResourceRepository<TDerived, TResourceType> > Handle;

				//=================================================================================
				// Protected Constructors
				//=================================================================================
				ResourceRepository(uint32 aReserveSize);
				~ResourceRepository();

				//=================================================================================
				// Protected Methods
				//=================================================================================
				inline void					Init(size_t aCapacity);

				inline Handle				Get(NoCaseStringHash32 aResourceNameId) const;
				inline Handle				Get(Handle aHandle) const;

				inline bool					HasResource(NoCaseStringHash32 aResourceNameId) const;

				inline Handle				Create(NoCaseStringHash32 aResourceNameId);
				inline void					Destroy(NoCaseStringHash32 aResourceNameId);
				inline void					Destroy(Handle aHandle);

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				Vector<TResourceType>					myResources;				
				VectorMap<NoCaseStringHash32, uint32>	myNameIdHashToIndex;
				BitVector<uint64>						myFreeIndices;
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
			
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		ResourceRepository<TDerived, TResourceType>::Handle ResourceRepository<TDerived, TResourceType>::Get(NoCaseStringHash32 aResourceNameId) const
		{
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
		ResourceRepository<TDerived, TResourceType>::Handle ResourceRepository<TDerived, TResourceType>::Get(NoCaseStringHash32 aResourceHandle) const
		{
			//const TResourceType* resource = myResources[itr->second];
			//resource->GetId();

			return Handle();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		bool ResourceRepository<TDerived, TResourceType>::HasResource(NoCaseStringHash32 aResourceNameId) const
		{
			return myNameIdHashToIndex.find(aResourceNameId) != myResources.end();
		}
	}
}