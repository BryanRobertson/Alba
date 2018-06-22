#pragma once

#include "Core.hpp"
#include "Core_ResourceId.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------------------
		// Name :	Resource<T>
		// Desc	:	Base class for all resource types
		//-----------------------------------------------------------------------------------------------------
		template <typename TDerived>
		class Resource
		{
			public:

				typedef NoCaseStringHash32 NameIdType;

				//=============================================================================================
				// Public Constructors
				//=============================================================================================
				inline Resource();
				explicit inline Resource(NameIdType aResourceNameId, ResourceId<TDerived> anId);
				
				inline Resource(const Resource<TDerived>& aCopyFrom) = delete;
				inline Resource(Resource<TDerived>&& aMoveFrom) = default;

				//=============================================================================================
				// Public Methods
				//=============================================================================================
				inline NameIdType				GetResourceNameId() const;
				inline ResourceId<TDerived>		GetId() const;

				Resource<TDerived>& operator= (const Resource<TDerived>& aCopyFrom) = delete;
				Resource<TDerived>& operator= (Resource<TDerived>&& aMoveFrom) = default;

			private:

				//=============================================================================================
				// Private Data
				//=============================================================================================
				NameIdType				myResourceNameId;
				ResourceId<TDerived>	myId;
		};

		//-----------------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------------
		template <typename TDerived>
		Resource<TDerived>::Resource()
			: myResourceNameId()
			, myId()
		{

		}

		//-----------------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------------
		template <typename TDerived>
		Resource<TDerived>::Resource(NoCaseStringHash32 aResourceNameId, ResourceId<TDerived> anId)
			: myResourceNameId(aResourceNameId)
			, myId(anId)
		{

		}

		//-----------------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------------
		template <typename TDerived>
		/*inline*/ typename Resource<TDerived>::NameIdType Resource<TDerived>::GetResourceNameId() const
		{
			return myResourceNameId;
		}

		//-----------------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------------
		template <typename TDerived>
		/*inline*/ ResourceId<TDerived>	Resource<TDerived>::GetId() const
		{
			return myId;
		}
	}
}