//------------------------------------------------------------------------------------------------
// Name      : Core_VectorSet.hpp
// Desc      : STL map type but implemented using a contiguous array
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/vector_map.h>

//------------------------------------------------------------------------------------------------
// Name	:	Core_VectorMap<T, Allocator>
//------------------------------------------------------------------------------------------------
template <typename TKey, typename TValueType, typename TCompare = eastl:less<TKey>, typename TAllocator = EASTLAllocatorDefault>
using Core_VectorMap = eastl::vector_map<TKey, TValueType, TCompare, TAllocator>;
