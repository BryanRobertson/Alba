#pragma once

//-------------------------------------------------------------------------------------------------
// Name      : Core_Mutex.hpp
// Desc      : Multithreading mutex type
// Author    : Bryan Robertson
// Date      : 2018/02/27
//-------------------------------------------------------------------------------------------------
#include "Core_AlignedStorage.hpp"
#include "Core_Optional.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	Mutex
		// Desc	:	Multithreading mutex lock
		//-----------------------------------------------------------------------------------------
		class Mutex final
		{
			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				explicit Mutex(Optional<int> anOptionalSpinCount = nullopt);
				~Mutex();

				//=================================================================================
				// Public Methods
				//=================================================================================
				void	Lock();
				bool	TryLock();
				void	Unlock();

				inline  void lock()				{ Lock();		}
				inline  bool try_lock()			{ TryLock();	}
				inline  void unlock()			{ Unlock();		}

			private:

				//=================================================================================
				// Private Constructors/Operators
				//=================================================================================

				// Non copiable, non movable
				Mutex(const Mutex& /*anOther*/)						{ }
				Mutex(const Mutex&& /*anOther*/)					{ }
				Mutex& operator= (const Mutex& /*anOther*/)			{ return *this; }
				Mutex& operator= (const Mutex&& /*anOther*/)		{ return *this; }

				//=================================================================================
				// Private Data
				//=================================================================================

				#ifdef ALBA_PLATFORM_WINDOWS
					// For now I'm using AlignedStorage to store the critical section
					// because otherwise I have to include <windows.h> everywhere mutex is used
					static const size_t ourBufferSize = 64;
					AlignedStorage<ourBufferSize>	myPlatformMutex;
				#endif
		};
	}
}