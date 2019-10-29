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
			for (;;)
			{
				
			}
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

		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		bool ReadWriteSpinLockMutex::try_lock_shared()
		{

		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void ReadWriteSpinLockMutex::unlock_shared()
		{

		}
	}
}