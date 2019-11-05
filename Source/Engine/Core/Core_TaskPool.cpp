#include "Core_Precompile.hpp"
#include "Core_TaskPool.hpp"

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
		void TaskPool::Init(uint aPoolSize)
		{
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
			
			return task;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TaskPool::FreeTask(Task* aTask)
		{
			{
				ScopedSpinlockMutexLock lock(myAllocFreeMutex);
				myTaskFreeList.Free(aTask);
			}			
		}
	}
}