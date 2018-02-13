//------------------------------------------------------------------------------------------------
// Name      : Core_Bitset.hpp
// Desc      : Equivalent to std::bitset
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/bitset.h>

//------------------------------------------------------------------------------------------------
// Name	:	Core_Bitset<N, WordType>
//------------------------------------------------------------------------------------------------
template <size_t N, typename WordType = EASTL_BITSET_WORD_TYPE_DEFAULT>
using Core_Bitset = eastl::bitset<N, WordType>;

