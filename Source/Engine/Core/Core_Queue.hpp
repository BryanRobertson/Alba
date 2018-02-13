//------------------------------------------------------------------------------------------------
// Name      : Core_Queue.hpp
// Desc      : STL Queue equivalent
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/queue.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Queue<T, Allocator>
		//------------------------------------------------------------------------------------------------
		template <typename TValueType, typename TContainer = Core_Deque<TValueType> >
		using Queue = eastl::queue<TValueType, TContainer>;
	}
}
