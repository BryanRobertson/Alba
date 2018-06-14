#pragma once

#include "Core_Config.hpp"
#include <EASTL/vector_multimap.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Core::VectorMultiMap<T, Allocator>
		//------------------------------------------------------------------------------------------------
		template <typename TKey, typename TValueType, typename TCompare = eastl::less<TKey>, typename TAllocator = EASTLAllocatorType>
		using VectorMultiMap = eastl::vector_multimap<TKey, TValueType, TCompare, TAllocator>;
	}
}
