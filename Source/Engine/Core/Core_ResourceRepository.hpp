#pragma once

#include "Core.hpp"
#include "Core_VectorMap.hpp"
#include "Core_StringHash.hpp"

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

				typedef SharedPtr<TResourceType> ResourcePtr;
				typedef WeakPtr<TResourceType> ResourceWeakPtr;

				//=================================================================================
				// Protected Constructors
				//=================================================================================
				ResourceRepository(uint32 aReserveSize);
				~ResourceRepository();

				//=================================================================================
				// Protected Methods
				//=================================================================================
				inline ResourcePtr			GetResource(NoCaseStringHash32 aResourceNameId) const;
				inline bool					HasResource(NoCaseStringHash32 aResourceNameId) const;

				inline ResourcePtr			AddResource(NoCaseStringHash32 aResourceNameId, ScopedPtr<TResourceType> aResource);
				inline void					RemoveResource(NoCaseStringHash32 aResourceNameId);

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				VectorMap<NoCaseStringHash32, ResourceWeakPtr> myResources;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		/*inline*/ ResourceRepository<TDerived, TResourceType>::ResourceRepository(uint32 aReserveSize)
		{
			myResources.Reserve(aReserveSize);
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