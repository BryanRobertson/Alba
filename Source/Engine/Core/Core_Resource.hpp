#pragma once

#include "Core.hpp"

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
				inline Resource(NameIdType aResourceNameId);

				inline Resource(const Resource<TDerived>& aCopyFrom) = delete;
				inline Resource(Resource<TDerived>&& aMoveFrom) = default;

				//=============================================================================================
				// Public Methods
				//=============================================================================================
				inline NameIdType GetResourceNameId() const;

				Resource<TDerived>& operator= (const Resource<TDerived>& aCopyFrom) = delete;
				Resource<TDerived>& operator= (Resource<TDerived>&& aMoveFrom) = default;

			protected:

				//=============================================================================================
				// Protected Methods
				//=============================================================================================
				inline void	SetResourceNameId(NameIdType aResourceNameId);

			private:

				//=============================================================================================
				// Private Data
				//=============================================================================================
				NameIdType	myResourceNameId;
		};

		//-----------------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------------
		template <typename TDerived>
		Resource<TDerived>::Resource(NoCaseStringHash32 aResourceNameId)
			: myResourceNameId(aResourceNameId)
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
		/*inline*/ void	typename Resource<TDerived>::SetResourceNameId(typename Resource<TDerived>::NameIdType aResourceNameId)
		{
			myResourceNameId = aResourceNameId;
		}
	}
}