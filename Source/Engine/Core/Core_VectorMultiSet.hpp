#pragma once

#include "Core_Config.hpp"
#include <EASTL/vector_multiset.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Core::VectorMultiSet<T, Allocator>
		//------------------------------------------------------------------------------------------------
		template <typename TValueType, typename TCompare = eastl::less<TValueType>, typename TAllocator = EASTLAllocatorType>
		using VectorMultiSet = eastl::vector_multiset<TValueType, TCompare, TAllocator>;
	}
}
