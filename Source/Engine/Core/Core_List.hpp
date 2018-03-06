//------------------------------------------------------------------------------------------------
// Name      : Core_List.hpp
// Desc      : STL List equivalent
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include <EASTL/list.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Core::List<T, Allocator>
		//------------------------------------------------------------------------------------------------
		template <typename TValueType, typename TAllocator = EASTLAllocatorType>
		using List = eastl::list<TValueType, TAllocator>;
	}
}
