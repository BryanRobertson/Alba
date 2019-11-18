#pragma once

#include "Core.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------------
		// Name : ThreadId
		// Desc : Thread Id type
		//-----------------------------------------------------------------------------------------------
		class ThreadId
		{
			public:

				friend ThreadId GetCurrentThreadId();

				//=======================================================================================
				// Public Static Data
				//=======================================================================================
				static const ThreadId Invalid;

				//=======================================================================================
				// Public Constructors
				//=======================================================================================
				constexpr ThreadId() = default;
				constexpr ThreadId(const ThreadId&) = default;
				constexpr ThreadId(ThreadId&&) = default;

				//=======================================================================================
				// Public Methods
				//=======================================================================================
				ALBA_FORCEINLINE constexpr bool operator==(const ThreadId& aThreadId) const noexcept { return myThreadId == aThreadId.myThreadId; }
				ALBA_FORCEINLINE constexpr bool operator!=(const ThreadId& aThreadId) const noexcept { return myThreadId != aThreadId.myThreadId; }
				ALBA_FORCEINLINE constexpr bool operator<=(const ThreadId& aThreadId) const noexcept { return myThreadId <= aThreadId.myThreadId; }
				ALBA_FORCEINLINE constexpr bool operator>=(const ThreadId& aThreadId) const noexcept { return myThreadId >= aThreadId.myThreadId; }
				ALBA_FORCEINLINE constexpr bool operator<(const ThreadId& aThreadId) const noexcept { return myThreadId < aThreadId.myThreadId; }
				ALBA_FORCEINLINE constexpr bool operator>(const ThreadId& aThreadId) const noexcept { return myThreadId > aThreadId.myThreadId; }

				ALBA_FORCEINLINE constexpr int32 Get() const noexcept { return myThreadId;  }

				constexpr ThreadId& operator=(const ThreadId& aThreadId) noexcept = default;
				constexpr ThreadId& operator=(ThreadId&& aThreadId) noexcept = default;

			private:

				//=======================================================================================
				// Private Constructors
				//=======================================================================================
				constexpr ThreadId(int32 anId)
					: myThreadId(anId)
				{

				}

				//=======================================================================================
				// Private Data
				//=======================================================================================
				int32 myThreadId = 0;
		};

		//-----------------------------------------------------------------------------------------------
		// Name : GetCurrentThreadId
		// Desc : Get the thread ID of the currently running thread
		//-----------------------------------------------------------------------------------------------
		extern ThreadId GetCurrentThreadId();
	}
}