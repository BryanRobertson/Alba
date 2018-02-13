//------------------------------------------------------------------------------------------------
// Name      : Core_VectorSet.hpp
// Desc      : STL set type but implemented using a contiguous array
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/vector_set.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Core::VectorSet<T, Allocator>
		//------------------------------------------------------------------------------------------------
		template <typename TValueType, typename TCompare = eastl:less<TValueType>, typename TAllocator = EASTLAllocatorDefault>
		using VectorSet = eastl::vector_set<TValueType, TCompare, TAllocator>;
	}
}
