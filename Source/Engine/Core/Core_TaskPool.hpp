#pragma once

#include "Core.hpp"
#include "Core_Thread.hpp"
#include "Core_Array.hpp"
#include "Core_Task.hpp"
#include "Core_AlignedStorage.hpp"
#include "Core_Platform.hpp"

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
				TaskPool()
				{
					
				}

				//================================================================================
				// Public Methods
				//================================================================================
				
				//--------------------------------------------------------------------------------
				//--------------------------------------------------------------------------------
				void Reset()
				{
					for (uint32 index = myFrameStartIndex; index != myFrameEndIndex; index=(index+1) & ourMask)
					{
						DeallocateTask(&myTaskStorage[index]);
					}

					myFrameStartIndex = myFrameEndIndex = myNextFreeTaskIndex = 0u;
				}

				//--------------------------------------------------------------------------------
				//--------------------------------------------------------------------------------
				template <typename... TArgs>
				Task* CreateTask(TArgs&&... someArgs)
				{
					TaskStorage* taskStorage = AllocateTask();
					new (taskStorage) Task(std::forward<TArgs>(someArgs)...);
				}

				//--------------------------------------------------------------------------------
				//--------------------------------------------------------------------------------
				void DestructTask(Task& aTask)
				{
					TaskStorage* storage = reinterpret_cast<TaskStorage*>(&task);
					aTask.~Task();

					DeallocateTask(storage);
				}

			private:

				//================================================================================
				// Private Constants
				//================================================================================
				static constexpr size_t ourMaxTasks = Core::NextLargestPowerOfTwo(TMaxSize);
				static constexpr size_t ourMask = ourMaxTasks - 1;

				//================================================================================
				// Private Types
				//================================================================================
				using TaskStorage = AlignedStorage<sizeof(Task), Core::HardwareConstants::theL1CacheLineSize>;

				//================================================================================
				// Private Methods
				//================================================================================

				//--------------------------------------------------------------------------------
				//--------------------------------------------------------------------------------
				TaskStorage* AllocateTask()
				{
					const uint32 index = ++myNextFreeTaskIndex;
					ALBA_ASSERT(index < myTaskPool.size());

					const uint32 aModIndex = (index - 1) & (ourMaxTasks - 1);
					myFrameEndIndex = aModIndex;

					ALBA_ASSERT(myFrameEndIndex != myFrameStartIndex, "Max tasks exceeded! Task pool has wrapped around!");
					return &myTaskPool[aModIndex];
				}

				void DeallocateTask(TaskStorage* aStorage)
				{
					ALBA_ASSERT(std::distance(aStorage, &myTasks[0]) >= 0 && std::distance(aStorage, &myTasks[0]) < TMaxSize);
					(void)aStorage;
				}

				//================================================================================
				// Private Data
				//================================================================================
				thread_local Array<TaskStorage, TMaxSize>	myTasks;

				thread_local uint32							myNextFreeTaskIndex = 0u;
				thread_local uint32							myFrameStartIndex = 0u;
				thread_local uint32							myFrameEndIndex = 0u;
		};
	}
}