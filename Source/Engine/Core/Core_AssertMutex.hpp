#pragma once

#include "Core_Mutex.hpp"

#if !defined(ALBA_RETAIL_BUILD) && !defined(ALBA_DEBUG_ASSERTMUTEX_ENABLED)
	#define ALBA_DEBUG_ASSERTMUTEX_ENABLED 1
#endif

//-------------------------------------------------------------------------------------------------
// Name      : Core_AssertMutex.hpp
// Desc      : Mutex to detect contention where it shouldn't exist, asserts if more than one
//			   lock is taken at the same time
//
// Author    : Bryan Robertson
// Date      : 2018/05/06
//-------------------------------------------------------------------------------------------------
namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		class AssertMutex final
		{
			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				AssertMutex();
				~AssertMutex();

				//=================================================================================
				// Public Methods
				//=================================================================================
				void	lock();
				void	unlock();

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				std::thread::id		myLockThreadId;
				std::mutex			myMutex;
		};

		typedef std::lock_guard<AssertMutex>	ScopedAssertMutexLock;
	}
}