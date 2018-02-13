//------------------------------------------------------------------------------------------------
// Name      : Core_HashMap.hpp
// Desc      : Hash Map type
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/hash_map.h>

//------------------------------------------------------------------------------------------------
// Name	:	Core_HashMap<Key, Value, Hash, Predicate, Allocator>
//------------------------------------------------------------------------------------------------
template <typename TKeyType, typename TValueType, typename THash = eastl::hash<TKeyType>, TPredicate = eastl::equal_to<TKeyType>, typename TAllocator = EASTLAllocatorDefault>
using Core_HashMap = eastl::hash_map<TKeyType, TValueType, THash, TPredicate, TAllocator>;

