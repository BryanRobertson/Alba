#pragma once

//-------------------------------------------------------------------------------------------------
// Name      : Core_Mutex.hpp
// Desc      : Multithreading mutex type
// Author    : Bryan Robertson
// Date      : 2018/02/27
//-------------------------------------------------------------------------------------------------
#include "Core.hpp"
#include <mutex>
#include <shared_mutex>

namespace Alba
{
	namespace Core
	{
		using Mutex					= std::mutex;
		using ReadWriteMutex		= std::shared_mutex;
		using TimedMutex			= std::timed_mutex;
		using ReadWriteTimedMutex	= std::shared_timed_mutex;

		using ScopedMutexLock		= std::lock_guard<std::mutex>;
		using ScopedReaderMutexLock	= std::shared_lock<std::shared_mutex>;
		using ScopedWriterMutexLock = std::unique_lock<std::shared_mutex> ;
	}
}