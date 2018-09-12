//------------------------------------------------------------------------------------------------
// Name      : Core_Array.hpp
// Desc      : Static array wrapper type
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include "Core_TypeTraits.hpp"
#include <array>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Core::Array<T, N>
		//------------------------------------------------------------------------------------------------
		template <typename TValueType, size_t TSize>
		using Array = std::array<TValueType, TSize>;

		//------------------------------------------------------------------------------------------------
		// Name	:	MakeArray
		// Desc	:	Generate a sized std::array from variadic arguments
		//------------------------------------------------------------------------------------------------
		template <typename... TValueType>
		constexpr auto MakeArray(TValueType&&... anInitList)
			-> Array<std::decay_t<std::common_type_t<TValueType...> >, sizeof...(anInitList)>
		{
			return Array<std::decay_t<std::common_type_t<TValueType...> >, sizeof...(anInitList)>
			(
				{ std::forward<std::decay_t<std::common_type_t<TValueType...> > >(anInitList)... }
			);
		}
	}
}

