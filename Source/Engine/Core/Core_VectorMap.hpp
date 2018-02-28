//------------------------------------------------------------------------------------------------
// Name      : Core_VectorSet.hpp
// Desc      : STL map type but implemented using a contiguous array
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/vector_map.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Core::VectorMap<T, Allocator>
		//------------------------------------------------------------------------------------------------
		template <typename TKey, typename TValueType, typename TCompare = eastl:less<TKey>, typename TAllocator = EASTLAllocatorType>
		using VectorMap = eastl::vector_map<TKey, TValueType, TCompare, TAllocator>;
	}
}

