
//------------------------------------------------------------------------------------------------
// Name	:	Core_Thread.hpp
// Desc	:	Wrapper around std::thread
//------------------------------------------------------------------------------------------------

#pragma once

#include <thread>
#include <atomic>

namespace Alba
{
	namespace Core
	{
		//-------------------------------------------------------------------------------------------------
		// Name	:	Core_ThisThread
		// Desc	:	Namespace alias for std::this_thread, so we can switch out STL threads for a compatible
		//			implementation if necessary
		//-------------------------------------------------------------------------------------------------
		namespace ThisThread = std::this_thread;

		//-------------------------------------------------------------------------------------------------
		// Name	:	Core_Thread
		// Desc	:	Alias for std::thread, so we can switch out STL threads for a compatible
		//			implementation if necessary
		//-------------------------------------------------------------------------------------------------
		typedef std::thread Thread;

		//-------------------------------------------------------------------------------------------------
		// Name	:	Core_Atomic
		// Desc :	Alias for std::atomic
		//-------------------------------------------------------------------------------------------------
		template <typename TValueType>
		using Atomic = std::atomic<TValueType>;
	}
}

