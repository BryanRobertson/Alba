#pragma once

//------------------------------------------------------------------------------------------------
// Name      : Core_TupleUtils.hpp
// Desc      : Tuple-related utils functions
// Author    : Bryan Robertson
// Date      : 2019/03/23
//------------------------------------------------------------------------------------------------

#include "Core.hpp"
#include <tuple>

namespace Alba
{
	namespace Core
	{
		namespace Internal
		{
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			template <typename TType, size_t TSize>
			struct CreateSizedTupleInternal
			{
				static auto Create(TType&& aValue)
				{
					return std::tuple_cat
					(
						std::make_tuple(std::forward<TType>(aValue)), 
						CreateSizedTupleInternal<TType, TSize - 1>::Create
						(
							std::forward<TType>(aValue)
						)
					);
				}
			};

			template <typename TType>
			struct CreateSizedTupleInternal<TType, 1>
			{
				static auto Create(TType&& aValue)
				{
					return std::make_tuple(std::forward<TType>(aValue));
				}
			};
		}

		//-----------------------------------------------------------------------------------------
		// Name	:	CreateSizedTuple
		// Desc	:	Create a tuple of a single type, with the specified number of values
		//-----------------------------------------------------------------------------------------
		template <typename TType, size_t TSize>
		auto CreateSizedTuple(TType&& aValue)
		{
			if constexpr (TSize == 0)
			{
				return std::tuple<>();
			}

			return Internal::CreateSizedTupleInternal<TType, TSize>::Create(std::forward<TType>(aValue));
		}

		//-----------------------------------------------------------------------------------------
		// Name	:	InvokeForEach
		// Desc	:	Invoke the passed in function for each passed in argument
		//			and return a tuple with the return value for each call
		//-----------------------------------------------------------------------------------------
		template <typename TFunc, typename... TArgs>
		auto Invoke_ForEach(TFunc&& aFunc, TArgs&&... someArgs)
		{
			return std::make_tuple(aFunc(std::forward<TArgs>(someArgs))...);
		}
	}
}