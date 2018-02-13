//------------------------------------------------------------------------------------------------
// Name      : Core_VectorSet.hpp
// Desc      : STL set type but implemented using a contiguous array
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/vector_set.h>

//------------------------------------------------------------------------------------------------
// Name	:	Core_VectorSet<T, Allocator>
//------------------------------------------------------------------------------------------------
template <typename TValueType, typename TCompare = eastl:less<TValueType>, typename TAllocator = EASTLAllocatorDefault>
using Core_VectorSet = eastl::vector_set<TValueType, TCompare, TAllocator>;
