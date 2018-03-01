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

		template <typename T1, typename T2>
		auto MakePair(T1&& aFirst, T2&& aSecond)
		{
			return eastl::make_pair(std::forward<T1>(aFirst), std::forward<T2>(aSecond));
		}

		template <typename T1, typename T2>
		auto MakePair(const T1& aFirst, const T2& aSecond)
		{
			return eastl::make_pair(aFirst, aSecond);
		}
	}
}
