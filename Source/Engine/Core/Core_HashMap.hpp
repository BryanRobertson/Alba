//------------------------------------------------------------------------------------------------
// Name      : Core_HashMap.hpp
// Desc      : Hash Map type
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/hash_map.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Core::HashMap<Key, Value, Hash, Predicate, Allocator>
		//------------------------------------------------------------------------------------------------
		template <typename TKeyType, typename TValueType, typename THash = eastl::hash<TKeyType>, TPredicate = eastl::equal_to<TKeyType>, typename TAllocator = EASTLAllocatorDefault>
		using HashMap = eastl::hash_map<TKeyType, TValueType, THash, TPredicate, TAllocator>;
	}
}

