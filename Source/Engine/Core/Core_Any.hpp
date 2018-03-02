#pragma once

//------------------------------------------------------------------------------------------------
// Name      : Core_Any.hpp
// Desc      : Variant type
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#include "Core_API.hpp"

#include <EASTL/utility.h>
#include <EASTL/type_traits.h>
#include <EASTL/any.h>

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------------------
		// Name	:	Any
		// Desc	:	Class that can store an object of any type
		//-----------------------------------------------------------------------------------------------------
		class ALBA_CORE_API Any final
		{
			public:

				//=============================================================================================
				// Public Constructors
				//=============================================================================================
				Any();
				Any(const Any& anOther);
				Any(Any&& anOther);
				
				template <typename TDataType>
				explicit Any(const TDataType& aData)
					: myData(aData)
				{

				}

				template <typename TDataType>
				explicit Any(TDataType&& aData)
					: myData(aData)
				{

				}

				//=============================================================================================
				// Public Methods
				//=============================================================================================

				#if EASTL_RTTI_ENABLED
				inline const std::type_info& type() const EA_NOEXCEPT
				{
					return myData.type();
				}
				#endif	

				//---------------------------------------------------------------------------------------------
				// Name	:	operator=
				//---------------------------------------------------------------------------------------------
				template <typename TDataType>
				Any& operator= (TDataType&& aData)
				{
					myData = std::forward<std::decay<TDataType>::type>(aData);
					return *this;
				}

				Any& operator= (const Any& anOther)
				{
					myData = anOther.myData;
					return *this;
				}

				Any& operator= (Any&& anOther)
				{
					myData = std::move(anOther.myData);
					return *this;
				}

				//---------------------------------------------------------------------------------------------
				// Name	:	Set
				// Desc	:	Set the Any to a typed value
				//---------------------------------------------------------------------------------------------
				template <typename TDataType>
				void Set(TDataType&& aData)
				{
					myData = std::forward<std::decay<TDataType>::type>(aData);
				}

				template <typename TDataType>
				void Set(const TDataType& aData)
				{
					myData = std::forward<std::decay<TDataType>::type>(aData);
				}

				//---------------------------------------------------------------------------------------------
				// Name	:	IsSet
				// Desc	:	Return true if the Any contains a valid value
				//---------------------------------------------------------------------------------------------
				bool	IsSet() const;

				//---------------------------------------------------------------------------------------------
				// Name	:	Clear
				// Desc	:	Clear the Any so that it's empty
				//---------------------------------------------------------------------------------------------
				void	Clear();

				//---------------------------------------------------------------------------------------------
				// Name	:	Is<T>
				// Desc	:	Return true if the Any contains the specified type
				//---------------------------------------------------------------------------------------------
				template <typename TDataType>
				bool Is() const
				{
					return eastl::any_cast<const std::decay<TDataType>::type>(&myData) != nullptr;
				}

				//---------------------------------------------------------------------------------------------
				// Name	:	To<T>
				// Desc	:	Casts the Any to the specified type. Assumes that the Any actually contains that type
				//			Use Is<T> first if this isn't guaranteed
				//---------------------------------------------------------------------------------------------
				template <typename TDataType>
				const typename std::decay<TDataType>::type& To() const
				{
					const std::decay<TDataType>::type* value = eastl::any_cast<const std::decay<TDataType>::type>(&myData);
					ALBA_ASSERT(value, "Attempting to use To<T> on an Any that does not contain the specified type. Use Is<T> first");

					return *value;
				}

				template <typename TDataType>
				typename std::decay<TDataType>::type& To()
				{
					std::decay<TDataType>::type* value = eastl::any_cast<std::decay<TDataType>::type>(&myData);
					ALBA_ASSERT(value, "Attempting to use To<T> on an Any that does not contain the specified type. Use Is<T> first");

					return *value;
				}

			private:

				//========================================================================================
				// Private Data
				//========================================================================================
				eastl::any	myData;
		};
	}
}

