#pragma once

#include "Core.hpp"
#include "Core_ThreadId.hpp"
#include "Core_Atomic.hpp"
#include "Core_Profile.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------------
		// Name : SpinLockMutex
		// Desc : Mutex primitive that uses atomic operations instead of OS primitives
		//		  Intended for cases where the lock is held for a very short period of time
		//		  and contention is rare
		//-----------------------------------------------------------------------------------------------
		class SpinLockMutex final
		{
			public: 

				//=================================================================================
				// Public Constructors
				//=================================================================================
				SpinLockMutex() = default;
				SpinLockMutex(const SpinLockMutex&) = delete;
				SpinLockMutex(SpinLockMutex&&) = default;

				//=================================================================================
				// Public Methods
				//=================================================================================
				SpinLockMutex& operator=(const SpinLockMutex&) = delete;
				SpinLockMutex& operator=(SpinLockMutex&&) = default;

				inline void lock();
				inline bool try_lock();
				ALBA_FORCEINLINE void unlock();
				ALBA_FORCEINLINE bool IsLocked() const;

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				Atomic<int32>	myLockValue;
				ThreadId		myLockThreadId;
				uint32			myLockRecursionDepth = 0;
		};

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void SpinLockMutex::lock()
		{
			const ThreadId currentThreadId = GetCurrentThreadId();
			if (myLockThreadId == currentThreadId)
			{
				// Already locked
				return;
			}

			ALBA_PROFILE_SCOPED(SpinLockMutex_Lock);

			for (;;)
			{
				if (myLockValue.load(std::memory_order_relaxed) > 0)
				{
					YieldProcessor();
					continue;
				}

				if (!myLockValue.fetch_add(1, std::memory_order_acq_rel) == 1)
				{
					myLockValue.fetch_sub(1, std::memory_order_acq_rel);
					continue;
				}

				// Gained lock successfully
				ALBA_ASSERT(myLockThreadId == ThreadId::Invalid, "Gained lock successfully, but already locked by thread %d?", myLockThreadId.Get());
				myLockThreadId = currentThreadId;
				++myLockRecursionDepth;

				break;
			}
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		bool SpinLockMutex::try_lock()
		{
			const ThreadId currentThreadId = GetCurrentThreadId();
			if (myLockThreadId == currentThreadId)
			{
				// Already locked
				return true;
			}

			ALBA_PROFILE_SCOPED(SpinLockMutex_Lock);

			if (!myLockValue.fetch_add(1, std::memory_order_acq_rel) == 1)
			{
				myLockValue.fetch_sub(1, std::memory_order_acq_rel);
				return false;
			}

			// Gained lock successfully
			ALBA_ASSERT(myLockThreadId == ThreadId::Invalid, "Gained lock successfully, but already locked by thread %d?", myLockThreadId.Get());
			myLockThreadId = currentThreadId;
			++myLockRecursionDepth;

			return true;
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void SpinLockMutex::unlock()
		{
			const ThreadId currentThreadId = GetCurrentThreadId();
			ALBA_ASSERT(currentThreadId == myLockThreadId, "Attempting to lock a spinlock mutex owned by another thread!");

			if (currentThreadId != myLockThreadId)
			{
				return;
			}

			myLockThreadId = ThreadId::Invalid;
			--myLockRecursionDepth;

			// Release the lock
			myLockValue.fetch_sub(1, std::memory_order_acq_rel);
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		bool SpinLockMutex::IsLocked() const
		{
			return myLockValue.load(std::memory_order_acquire) > 0;
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		using ScopedSpinlockMutexLock = std::lock_guard<SpinLockMutex>;
	}
}