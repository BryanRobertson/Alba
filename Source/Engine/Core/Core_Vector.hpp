//------------------------------------------------------------------------------------------------
// Name      : Core_Vector.hpp
// Desc      : STL Vector equivalent
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/vector.h>

//------------------------------------------------------------------------------------------------
// Name	:	Core_Vector<T, Allocator>
//------------------------------------------------------------------------------------------------
template <typename TValueType, typename TAllocator = EASTLAllocatorDefault>
using Core_Vector = eastl::vector<TValueType, TAllocator>;
