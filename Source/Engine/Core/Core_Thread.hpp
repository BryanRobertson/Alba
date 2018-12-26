#pragma once

//------------------------------------------------------------------------------------------------
// Name	:	Core_Thread.hpp
// Desc	:	Wrapper around std::thread
//------------------------------------------------------------------------------------------------

#include "Core.hpp"
#include "Core_Time.hpp"

#include <thread>
#include <mutex>
#include <atomic>

namespace Alba
{
	namespace Core
	{
		//-------------------------------------------------------------------------------------------------
		// Name	:	Core::ThisThread
		// Desc	:	Namespace alias for std::this_thread, so we can switch out STL threads for a compatible
		//			implementation if necessary
		//-------------------------------------------------------------------------------------------------
		namespace ThisThread = std::this_thread;

		//-------------------------------------------------------------------------------------------------
		// Name	:	Core::Thread
		// Desc	:	Alias for std::thread, so we can switch out STL threads for a compatible
		//			implementation if necessary
		//-------------------------------------------------------------------------------------------------
		using Thread = std::thread;

		//-------------------------------------------------------------------------------------------------
		// Name	:	Core_Atomic
		// Desc :	Alias for std::atomic
		//-------------------------------------------------------------------------------------------------
		template <typename TValueType>
		using atomic = std::atomic<TValueType>;

		//-------------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------
		inline void Yield()
		{
			ThisThread::yield();
		}

		//-------------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------
		template <typename TUnits, typename TRatio>
		inline void Sleep(Duration<TUnits, TRatio> aDuration)
		{
			ThisThread::sleep_for(aDuration);
		}

		//-------------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------
		inline void SleepUntil(TimePoint aTimePoint)
		{
			ThisThread::sleep_until(aTimePoint);
		}
	}
}

