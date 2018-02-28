//------------------------------------------------------------------------------------------------
// Name      : Core_Set.hpp
// Desc      : STL set type
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/set.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Set<T, Hash, Predicate, Allocator>
		//------------------------------------------------------------------------------------------------
		template <typename TValueType, typename TCompare = eastl::less<TValueType>, typename TAllocator = EASTLAllocatorType>
		using Set = eastl::set<TValueType, TCompare, TPredicate, TAllocator>;
	}
}

