#pragma once

#include "Core.hpp"
#include "Core_Thread.hpp"
#include "Core_Array.hpp"
#include "Core_Task.hpp"

namespace Alba
{
	namespace Core
	{
		class Task;

		//-----------------------------------------------------------------------------------------
		// Name	:	TaskPool
		// Desc	:	Contains a fixed-size pool of task instances stored as a circular buffer
		//			As tasks are allocated, the buffer will eventually wrap around
		//			so a large enough size must be chosen to ensure that we don't overwrite tasks
		//			that are in progress
		//
		//			Note: that for efficiency reasons, TMaxSize will be rounded up to the next
		//				  largest power of two
		//-----------------------------------------------------------------------------------------
		template <size_t TMaxSize>
		class TaskPool final
		{
			public:

				//================================================================================
				// Public Constructors
				//================================================================================
				TaskPool() = default;

				//================================================================================
				// Public Methods
				//================================================================================

				//--------------------------------------------------------------------------------
				//--------------------------------------------------------------------------------
				template <typename... TArgs>
				Task& CreateTask(TArgs&&... someArgs)
				{
					Task& task = AllocateTask();
					task = std::move(Task(std::forward<Task>(someArgs)...));

					return task;
				}

				//--------------------------------------------------------------------------------
				//--------------------------------------------------------------------------------
				Task& AllocateTask()
				{
					const uint32 index = myNextFreeTaskIndex.fetch_add(1, std::memory_order_relaxed);
					ALBA_ASSERT(index < myTaskPool.size());

					Task& task = myTaskPool[(index - 1) & (ourMaxTasks - 1)];
					return task;
				}

			private:

				//================================================================================
				// Private Constants
				//================================================================================
				static const size_t ourMaxTasks = Core::NextLargestPowerOfTwo(TMaxSize);

				//================================================================================
				// Private Types
				//================================================================================

				//================================================================================
				// Private Data
				//================================================================================
				Array<Task, TMaxSize>	myTasks;
				atomic<uint32>			myNextFreeTaskIndex = 0u;
		};
	}
}