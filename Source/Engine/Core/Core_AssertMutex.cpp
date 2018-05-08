#include "Core_Precompile.hpp"
#include "Core_AssertMutex.hpp"
#include "Core_FixedStringStream.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		AssertMutex::AssertMutex()
			: myLockThreadId()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		AssertMutex::~AssertMutex()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void AssertMutex::lock()
		{
			#if ALBA_DEBUG_ASSERTMUTEX_ENABLED

			const std::thread::id currentThreadId = std::this_thread::get_id();
			if (myMutex.try_lock())
			{
				myLockThreadId = currentThreadId;
			}
			else
			{
				FixedStringStream<1024> errorStream;
				errorStream << "Assert mutex locked twice! Locked by threads: " << myLockThreadId << " and " << currentThreadId;
				errorStream.flush();

				ALBA_ASSERT(false, "%s", errorStream.str().c_str());
			}
			#endif
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void AssertMutex::unlock()
		{
			myLockThreadId = std::thread::id();
			myMutex.unlock();
		}
	}
}