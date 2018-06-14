//------------------------------------------------------------------------------------------------
// Name      : Core_BitSet.hpp
// Desc      : Equivalent to std::bitset
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include <EASTL/bitset.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Core::Bitset<N, WordType>
		//------------------------------------------------------------------------------------------------
		template <size_t N, typename WordType = EASTL_BITSET_WORD_TYPE_DEFAULT>
		using BitSet = eastl::bitset<N, WordType>;
	}
}