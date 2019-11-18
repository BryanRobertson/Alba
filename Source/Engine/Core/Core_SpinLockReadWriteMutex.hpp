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
		// Desc : Synchronisation primitive that can have exactly one writer, but many readers
		//		  Multiple readers can hold the lock simultaneously, or one writer can hold the lock.
		//
		//		  The lock is implemented using atomics internally, with a busy wait. So the intention
		//		  here is to use the lock in situations where the lock is held for a short duration only
		//-----------------------------------------------------------------------------------------------
		class ReadWriteSpinLockMutex final
		{
			public:

				//=======================================================================================
				// Public Constructors
				//=======================================================================================
				ReadWriteSpinLockMutex();

				//=======================================================================================
				// Public Methods
				//=======================================================================================

			private:

				//=======================================================================================
				// Private Data
				//=======================================================================================

		};
	}
}