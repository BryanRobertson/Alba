//------------------------------------------------------------------------------------------------
// Name      : Core_Vector.hpp
// Desc      : STL Vector equivalent
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include <EASTL/vector.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Core::Vector<T, Allocator>
		//------------------------------------------------------------------------------------------------
		template <typename TValueType, typename TAllocator = EASTLAllocatorType>
		using Vector = eastl::vector<TValueType, TAllocator>;
	}
}

