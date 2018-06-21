#pragma once

#include "Core.hpp"
#include "Core_VectorMap.hpp"
#include "Core_BitVector.hpp"
#include "Core_StringHash.hpp"
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

				inline Handle				GetResource(NoCaseStringHash32 aResourceNameId) const;
				inline Handle				GetResource(Handle aHandle) const;

				inline bool					HasResource(NoCaseStringHash32 aResourceNameId) const;

				inline Handle				CreateResource(NoCaseStringHash32 aResourceNameId);
				inline void					DestroyResource(NoCaseStringHash32 aResourceNameId);

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
			myResources.(aReserveSize);
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
		ResourceRepository<TDerived, TResourceType>::ResourcePtr ResourceRepository<TDerived, TResourceType>::GetResource(NoCaseStringHash32 aResourceNameId) const
		{
			auto itr = myResources.find(aResourcceNameId);
			if (itr != myResources.end())
			{
				return itr.second.lock();
			}

			return ResourcePtr();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		bool ResourceRepository<TDerived, TResourceType>::HasResource(NoCaseStringHash32 aResourceNameId) const
		{
			return myResources.find(aResourceNameId) != myResources.end();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		ResourceRepository<TDerived, TResourceType>::ResourcePtr ResourceRepository<TDerived, TResourceType>::AddResource(NoCaseStringHash32 aResourceNameId, ScopedPtr<TResourceType> aResource)
		{
			ALBA_ASSERT(!HasResource(aResourceNameId), "Trying to add duplicate resource %s", aResourceNameId.LogString().c_str());
			myResources.emplace(aResourceNameId, std::move(aResource));
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		void ResourceRepository<TDerived, TResourceType>::RemoveResource(NoCaseStringHash32 aResourceNameId)
		{
			myResources.erase(aResourceNameId);
		}
	}
}