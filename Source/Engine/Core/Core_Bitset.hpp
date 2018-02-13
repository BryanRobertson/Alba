//------------------------------------------------------------------------------------------------
// Name      : Core_Bitset.hpp
// Desc      : Equivalent to std::bitset
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/bitset.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Core::Bitset<N, WordType>
		//------------------------------------------------------------------------------------------------
		template <size_t N, typename WordType = EASTL_BITSET_WORD_TYPE_DEFAULT>
		using Bitset = eastl::bitset<N, WordType>;
	}

	namespace Test
	{
		static const Core::Bitset<32> TestBitSet;
	}
}