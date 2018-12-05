#include "Core_Precompile.hpp"
#include "Core_TaskPool.hpp"
#include "Core_Assert.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TaskPool::TaskPool()
		{
			myTaskStorage.fill(TaskPool::TaskStorage());
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TaskPool::~TaskPool()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TaskPool::Reset()
		{
			myNextFreeTaskIndex = 0;
			ALBA_ASSERT(myOpenTaskCount == 0, "Resetting task pool with tasks still active!");
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void* TaskPool::AllocateTask()
		{
			static constexpr size_t ourTaskStorageMask = ourTaskPoolSize - 1;

			const uint32 index = ++myNextFreeTaskIndex;
			++myOpenTaskCount;

			// For now, we don't allow this
			ALBA_ASSERT(index < myTaskStorage.size(), "Task pool has wrapped around!");

			const size_t aModIndex = (index - 1) & ourTaskStorageMask;
			return &myTaskStorage[aModIndex];
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ void TaskPool::DeallocateTask(Task& aTask)
		{
			TaskStorage* taskStorage = reinterpret_cast<TaskStorage*>(&aTask);
			(void) taskStorage;

			ALBA_ASSERT
			(
				taskStorage >= &(*myTaskStorage.begin()) && taskStorage < &(*myTaskStorage.end()),
				"Attempted to free task that doesn't belong to this task pool!"
			);
			
			aTask.~Task();
			--myOpenTaskCount;
		}
	}
}