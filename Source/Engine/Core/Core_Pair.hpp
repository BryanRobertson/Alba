#pragma once

//------------------------------------------------------------------------------------------------
// Name      : Core_Pair.hpp
// Desc      : Equivalent to std::pair
// Author    : Bryan Robertson
// Date      : 2017/02/27
//------------------------------------------------------------------------------------------------
#include <EASTL/utility.h>

namespace Alba
{
	namespace Core
	{
		template <typename TFirst, typename TSecond>
		using Pair = eastl::pair<TFirst, TSecond>;

		template <typename TFirst, typename TSecond>
		constexpr auto MakePair(TFirst&& aFirst, TSecond&& aSecond) 
			-> decltype( eastl::make_pair(std::forward(aFirst), std::forward(aSecond)) )
		{
			return eastl::make_pair(std::forward(aFirst), std::forward(aSecond));
		}
	}
}
