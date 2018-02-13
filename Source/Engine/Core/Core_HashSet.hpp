//------------------------------------------------------------------------------------------------
// Name      : Core_HashSet.hpp
// Desc      : Hash set type
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/hash_set.h>

//------------------------------------------------------------------------------------------------
// Name	:	Core_HashSet<T, Hash, Predicate, Allocator>
//------------------------------------------------------------------------------------------------
template <typename TValueType, typename THash = eastl::hash<TValueType>, TPredicate = eastl::equal_to<TValueType>, typename TAllocator = EASTLAllocatorDefault>
using Core_HashSet = eastl::hash_set<TValueType, THash, TPredicate, TAllocator>;
