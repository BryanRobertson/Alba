
//------------------------------------------------------------------------------------------------
// Name	:	Core_Thread.hpp
// Desc	:	Wrapper around std::thread
//------------------------------------------------------------------------------------------------

#pragma once

#include <thread>
#include <atomic>

//-------------------------------------------------------------------------------------------------
// Name	:	Core_ThisThread
// Desc	:	Namespace alias for std::this_thread, so we can switch out STL threads for a compatible
//			implementation if necessary
//-------------------------------------------------------------------------------------------------
namespace Core_ThisThread = std::this_thread;

//-------------------------------------------------------------------------------------------------
// Name	:	Core_Thread
// Desc	:	Alias for std::thread, so we can switch out STL threads for a compatible
//			implementation if necessary
//-------------------------------------------------------------------------------------------------
typedef std::thread Core_Thread;

//-------------------------------------------------------------------------------------------------
// Name	:	Core_Atomic
// Desc :	Alias for std::atomic
//-------------------------------------------------------------------------------------------------
template <typename TValueType>
using Core_Atomic = std::atomic<TValueType>;
