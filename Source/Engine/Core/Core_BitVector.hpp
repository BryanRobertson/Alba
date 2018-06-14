#pragma once

#include "Core_Config.hpp"
#include <EASTL/bitvector.h>
#include <EASTL/allocator.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Core::BitVector<N, WordType>
		//------------------------------------------------------------------------------------------------
		template <typename TElementType, typename TAllocator = EASTLAllocatorType>
		using BitVector = eastl::bitvector<TAllocator, TElementType>;
	}
}
