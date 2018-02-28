//------------------------------------------------------------------------------------------------
// Name      : Core_Map.hpp
// Desc      : Map type
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/map.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Core::Map<Key, Value, Hash, Predicate, Allocator>
		//------------------------------------------------------------------------------------------------
		template <typename TKeyType, typename TValueType, typename TCompare = eastl::less<TKeyType>, TPredicate = eastl::equal_to<TValueType>, typename TAllocator = EASTLAllocatorType>
		using Map = eastl::map<TKeyType, TValueType, THash, TPredicate, TAllocator>;
	}
}

