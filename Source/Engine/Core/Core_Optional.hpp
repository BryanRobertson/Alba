#pragma once

//-------------------------------------------------------------------------------------------------
// Name      : Core_Optional.hpp
// Desc      : Equivalent to std::optional
// Author    : Bryan Robertson
// Date      : 2018/02/28
//-------------------------------------------------------------------------------------------------
#include "Core.hpp"
#include <EASTL/optional.h>

namespace Alba
{
	namespace Core
	{
		template <typename TValueType>
		using Optional = eastl::optional<TValueType>;

		using eastl::nullopt_t;
		using eastl::nullopt;

		template <typename TValueType>
		constexpr auto MakeOptional(TValueType&& aValue) -> decltype( eastl::make_optional(std::forward(aValue)) )
		{
			return eastl::make_optional(std::forward(aValue));
		}	
	}
}
