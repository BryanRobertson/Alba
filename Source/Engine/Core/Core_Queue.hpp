//------------------------------------------------------------------------------------------------
// Name      : Core_Queue.hpp
// Desc      : STL Queue equivalent
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/queue.h>

//------------------------------------------------------------------------------------------------
// Name	:	Core_Queue<T, Allocator>
//------------------------------------------------------------------------------------------------
template <typename TValueType, typename TContainer = Core_Deque<TValueType> >
using Core_Queue = eastl::queue<TValueType, TContainer>;
