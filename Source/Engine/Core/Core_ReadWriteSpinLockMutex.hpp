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
		// Name : ReadWriteSpinLockMutex
		// Desc : A synchronisation primitive that can be locked by exactly one writer, or multiple
		//		  readers.
		//
		//		 The lock is implemented using atomics and busy-waiting internally, so this lock should
		//		 only be used in situations where the lock is held for a very short length of time
		//		 (e.g. to swap a pointer)
		//-----------------------------------------------------------------------------------------------
		class ReadWriteSpinLockMutex
		{
			public:

				//=======================================================================================
				// Public Constructors
				//=======================================================================================
				ReadWriteSpinLockMutex() = default;
				ReadWriteSpinLockMutex(const ReadWriteSpinLockMutex&) = delete;
				ReadWriteSpinLockMutex(ReadWriteSpinLockMutex&&) = delete;

				//=======================================================================================
				// Public Methods
				//=======================================================================================
				ReadWriteSpinLockMutex& operator=(const ReadWriteSpinLockMutex&) = delete;
				ReadWriteSpinLockMutex& operator=(ReadWriteSpinLockMutex&&) = delete;

				// Write lock
				inline void lock();
				inline bool try_lock();
				ALBA_FORCEINLINE void unlock();

				// Read lock
				inline void lock_shared();
				inline bool try_lock_shared();
				ALBA_FORCEINLINE void unlock_shared();

			private:

				//=======================================================================================
				// Private Static Data
				//=======================================================================================
				static constexpr uint32 ourReaderMask = 0x7fffff;
				static constexpr uint32 ourWriterValue = ourReaderMask + 1;

				//=======================================================================================
				// Private Data
				//=======================================================================================
				Atomic<int32>	myLockValue;
				ThreadId		myLockThreadId;
				uint32			myLockRecursionDepth = 0;
		};

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void ReadWriteSpinLockMutex::lock()
		{
			
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		bool ReadWriteSpinLockMutex::try_lock()
		{

		}
		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void ReadWriteSpinLockMutex::unlock()
		{

		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void ReadWriteSpinLockMutex::lock_shared()
		{
			ALBA_PROFILE_SCOPED(ReadWriteSpinLockMutex_LockRead);

			for (;;)
			{
				if ((myLockValue.load(std::memory_order_relaxed) & ~ourReaderMask) != 0)
				{
					YieldProcessor();
					continue;
				}

				// Can get reader lock as long as none of the writer bits are set
				if ((myLockValue.fetch_add(1, std::memory_order_acq_rel) & ~ourReaderMask) != 0)
				{
					myLockValue.fetch_sub(1, std::memory_order_acq_rel);
					continue;
				}

				// Gained lock successfully
				break;
			}
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		bool ReadWriteSpinLockMutex::try_lock_shared()
		{
			ALBA_PROFILE_SCOPED(ReadWriteSpinLockMutex_LockRead);

			if ((myLockValue.fetch_add(1, std::memory_order_acq_rel) & ourReaderMask) != 0)
			{
				myLockValue.fetch_sub(1, std::memory_order_acq_rel);
				return false;
			}

			// Gained lock successfully
			return true;
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void ReadWriteSpinLockMutex::unlock_shared()
		{
			ALBA_ASSERT(myLockValue.load(std::memory_order_relaxed) > 0);

			// Release the lock
			myLockValue.fetch_sub(1, std::memory_order_acq_rel);
		}
	}
}