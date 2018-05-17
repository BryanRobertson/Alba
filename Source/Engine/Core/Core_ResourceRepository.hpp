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

				//=================================================================================
				// Protected Constructors
				//=================================================================================
				ResourceRepository(uint32 aReserveSize);
				~ResourceRepository();

				//=================================================================================
				// Protected Methods
				//=================================================================================
				inline const ResourcePtr	GetResource(NoCaseStringHash32 aResourceNameId) const
				inline ResourcePtr			GetResourceMutable(NoCaseStringHash32 aResourceNameId);
				inline bool					HasResource(NoCaseStringHash32 aResourceNameId) const;

				inline ResourcePtr&			AddResource(NoCaseStringHash32 aResourceNameId);
				inline void					RemoveResource(NoCaseStringHash32 aResourceNameId);

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				VectorMap<NoCaseStringHash32, TResourceType> myResources;
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
		const ResourceRepository<TDerived, TResourceType>::ResourcePtr ResourceRepository<TDerived, TResourceType>::GetResource(NoCaseStringHash32 aResourceNameId) const
		{
			
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		ResourceRepository<TDerived, TResourceType>::ResourcePtr ResourceRepository<TDerived, TResourceType>::GetResourceMutable(NoCaseStringHash32 aResourceNameId)
		{
			
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TDerived, typename TResourceType>
		bool ResourceRepository<TDerived, TResourceType>::HasResource(NoCaseStringHash32 aResourceNameId) const
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		inline ResourcePtr&			AddResource(NoCaseStringHash32 aResourceNameId);
		inline void					RemoveResource(NoCaseStringHash32 aResourceNameId);
	}
}