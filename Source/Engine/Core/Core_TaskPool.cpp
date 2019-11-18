#include "Core_Precompile.hpp"
#include "Core_TaskPool.hpp"
#include "Core_TaskInternal.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TaskPool::TaskPool()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TaskPool::~TaskPool()
		{
			
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TaskPool::Init(TaskThreadId aThreadId, uint aPoolSize)
		{
			myThreadId = aThreadId;

			myTaskBuffer.resize(aPoolSize);
			myTaskFreeList.Init((byte*)myTaskBuffer.begin(), (byte*)myTaskBuffer.end());
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Task* TaskPool::AllocateTask()
		{
			Task* task = nullptr;
			{
				ScopedSpinlockMutexLock lock(myAllocFreeMutex);
				task = (Task*)myTaskFreeList.Allocate();
			}

			ALBA_ASSERT(task, "Failed to allocate task!");

			{
				const size_t index = ((byte*)task - (byte*)myTaskBuffer.begin()) / sizeof(AlignedStorageT<Task>);

				task->myTaskId = TaskInternal::CombineTaskId(myThreadId, static_cast<uint16>(index), myCounter);
			}
			
			return task;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TaskPool::FreeTask(Task* aTask)
		{
			{
				ScopedSpinlockMutexLock lock(myAllocFreeMutex);

				aTask->myTaskId.Invalidate();
				myTaskFreeList.Free(aTask);
			}			
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		const Task* TaskPool::GetTask(TaskId aTaskId) const
		{
			ALBA_ASSERT(TaskInternal::GetThreadId(aTaskId) == myThreadId);

			const uint16 taskIndex = TaskInternal::GetTaskIndex(aTaskId);

			const void* ptr = &(myTaskBuffer[taskIndex].mCharData);
			const Task* taskPtr = nullptr;

			std::memcpy(&taskPtr, &ptr, sizeof(taskPtr));

			// ID no longer matches
			if (taskPtr->myTaskId != aTaskId)
			{
				return nullptr;
			}

			return taskPtr;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Task* TaskPool::GetTaskMutable(TaskId aTaskId)
		{
			ALBA_ASSERT(TaskInternal::GetThreadId(aTaskId) == myThreadId);

			const uint16 taskIndex = TaskInternal::GetTaskIndex(aTaskId);

			void* ptr = &(myTaskBuffer[taskIndex].mCharData);
			Task* taskPtr = nullptr;

			std::memcpy(&taskPtr, &ptr, sizeof(taskPtr));

			// ID no longer matches
			if (taskPtr->myTaskId != aTaskId)
			{
				return nullptr;
			}

			return taskPtr;
		}
	}
}