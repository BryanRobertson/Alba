//------------------------------------------------------------------------------------------------
// Name      : Core_Stack.hpp
// Desc      : STL Stack equivalent
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/stack.h>

//------------------------------------------------------------------------------------------------
// Name	:	Core_Stack<T, Allocator>
//------------------------------------------------------------------------------------------------
template <typename TValueType, typename TContainer=Core_Vector<TValueType> >
using Core_Stack = eastl::stack<TValueType, TContainer>;
