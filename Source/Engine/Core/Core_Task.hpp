#pragma once

#include "Core.hpp"
#include "Core_Thread.hpp"
#include "Core_Function.hpp"
#include "Core_Platform.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		struct Task
		{
			//=====================================================================================
			// Public Constructors
			//=====================================================================================
			Task() = default;
			Task(const Task&) = delete;
			Task(Task&&) = default;

			//=====================================================================================
			// Public Data
			//=====================================================================================

			// Task Id
			uint32			myId			= 0;

			// Id of parent task
			uint32			myParentId		= 0;

			// Id of task that this task depends on
			uint32			myDependsOn		= 0;

			// Count of tasks that have yet to complete
			atomic<uint32>	myOpenChildCount = 0;

			// Priority of task
			uint8			myPriority		= 0;

			// Keep this up to date: We want sizeof(Task) to take up at least a whole cache-line
			static constexpr int64 ourRequiredPaddingSize = HardwareConstants::theL1CacheLineSize
															- sizeof(myId)
															- sizeof(myParentId)
															- sizeof(myDependsOn)
															- sizeof(myOpenChildCount)
															- sizeof(myPriority)
															- sizeof(FixedFunction<void(), 0>);

			static_assert(ourRequiredPaddingSize > 0);

			// Task function - use all remaining size for the function's fixed-size buffer
			FixedFunction<void(), ourRequiredPaddingSize> myTaskFunction;
		};

		// Note: This can be commented out - it doesn't matter if Task is larger than the cache-line size
		//		 I just want to know when it happens
		static_assert(sizeof(Task) == HardwareConstants::theL1CacheLineSize, "sizeof(Task) > cache line size");
	}
}