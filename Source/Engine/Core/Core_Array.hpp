//------------------------------------------------------------------------------------------------
// Name      : Core_Array.hpp
// Desc      : Static array wrapper type
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/array.h>

//------------------------------------------------------------------------------------------------
// Name	:	Core_Array<T, N>
//------------------------------------------------------------------------------------------------
template <typename TValueType, size_t N>
using Core_Array = eastl::array<TValueType, N>;
