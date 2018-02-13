//------------------------------------------------------------------------------------------------
// Name      : Core_List.hpp
// Desc      : STL List equivalent
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/list.h>

//------------------------------------------------------------------------------------------------
// Name	:	Core_List<T, Allocator>
//------------------------------------------------------------------------------------------------
template <typename TValueType, typename TAllocator = EASTLAllocatorDefault>
using Core_List = eastl::list<TValueType, TAllocator>;
