#include "Core_Precompile.hpp"
#include "Core_Mutex.hpp"

#ifdef ALBA_PLATFORM_WINDOWS
	#define NOMINMAX
	#include <Windows.h>
	#undef NOMINMAX
#endif

namespace Alba
{
	namespace Core
	{
#ifdef ALBA_PLATFORM_WINDOWS

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		Mutex::Mutex(Optional<int> anOptionalSpinCount)
		{
			static_assert
			(
				ourBufferSize >= sizeof(CRITICAL_SECTION),
				"Buffer in Mutex is insufficient to hold a CRITICAL_SECTION. Increase ourBufferSize"
			);

			CRITICAL_SECTION* criticalSection = new (&myPlatformMutex) CRITICAL_SECTION;
			const int spinCount = anOptionalSpinCount.value_or(4000);

			::InitializeCriticalSectionAndSpinCount(criticalSection, spinCount);
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		Mutex::~Mutex()
		{
			CRITICAL_SECTION* criticalSection = reinterpret_cast<CRITICAL_SECTION*>(&myPlatformMutex);
			::DeleteCriticalSection(criticalSection);
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void Mutex::Lock()
		{
			CRITICAL_SECTION* criticalSection = reinterpret_cast<CRITICAL_SECTION*>(&myPlatformMutex);
			::EnterCriticalSection(criticalSection);
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		bool Mutex::TryLock()
		{
			CRITICAL_SECTION* criticalSection = reinterpret_cast<CRITICAL_SECTION*>(&myPlatformMutex);
			return ::TryEnterCriticalSection(criticalSection) != FALSE;
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void Mutex::Unlock()
		{
			CRITICAL_SECTION* criticalSection = reinterpret_cast<CRITICAL_SECTION*>(&myPlatformMutex);
			::LeaveCriticalSection(criticalSection);
		}
#endif
	}
}