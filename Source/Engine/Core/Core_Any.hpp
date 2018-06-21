#pragma once

//------------------------------------------------------------------------------------------------
// Name      : Core_Any.hpp
// Desc      : Class that can store an object of any type
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#include "Core.hpp"
#include "Core_TypeTraits.hpp"

#include <EASTL/utility.h>
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
				Any(const Any& aCopyFrom);
				Any(Any&& aMoveFrom);
				
				template <typename TDataType>
				explicit Any(const TDataType& aData)
				{
					myData = TDataType(aData);
				}

				template <typename TDataType, class=enable_if_t<!is_lvalue_reference_v<TDataType>> >
				explicit Any(TDataType&& aData)
				{
					myData = std::move(aData);
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
					Set(std::move(aData));
					return *this;
				}

				template <typename TDataType>
				Any& operator= (const TDataType& aData)
				{
					Set(aData);
					return *this;
				}

				Any& operator= (const Any& aCopyFrom)
				{
					if (aCopyFrom.myData.has_value())
					{
						myData = aCopyFrom.myData;
					}
					
					return *this;
				}

				Any& operator= (Any&& aMoveFrom)
				{
					if (aMoveFrom.myData.has_value())
					{
						myData = std::move(aMoveFrom.myData);
					}
					
					return *this;
				}

				//---------------------------------------------------------------------------------------------
				// Name	:	Set
				// Desc	:	Set the Any to a typed value
				//---------------------------------------------------------------------------------------------
				template <typename TDataType, class = enable_if_t<!is_lvalue_reference<TDataType>> >
				void Set(TDataType&& aData)
				{
					myData.emplace(std::move(aData));
				}

				template <typename TDataType>
				void Set(const TDataType& aData)
				{
					myData = std::move(TDataType(aData));
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
					const auto* value = eastl::any_cast<const std::decay<TDataType>::type>(&myData);
					ALBA_ASSERT(value != nullptr, "Attempting to use To<T> on an Any that does not contain the specified type. Use Is<T> first");

					return *value;
				}

				template <typename TDataType>
				typename std::decay<TDataType>::type& To()
				{
					auto* value = eastl::any_cast<std::decay<TDataType>::type>(&myData);
					ALBA_ASSERT(value != nullptr, "Attempting to use To<T> on an Any that does not contain the specified type. Use Is<T> first");

					return *value;
				}

			private:

				//========================================================================================
				// Private Data
				//========================================================================================
				eastl::any	myData;
		};

		template <typename T>
		auto MakeAny(T&& aData)
		{
			return Any(std::move(aData));
		}

		template <typename T>
		auto MakeAny(const T& aData)
		{
			return Any(aData);
		}
	}
}

