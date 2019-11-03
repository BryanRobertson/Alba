#pragma once

#include "Core.hpp"
#include "Core_TaskTypes.hpp"
#include "Core_TaskIdTypes.hpp"
#include "Core_Task.hpp"
#include "Core_FreeList.hpp"
#include "Core_TaskPtr.hpp"
#include "Core_SpinLockMutex.hpp"
#include "Core_Vector.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	: TaskPool
		//-----------------------------------------------------------------------------------------
		class TaskPool final
		{
			public:

				friend class TaskSystem;

				//=================================================================================
				// Public Constructors
				//=================================================================================
				TaskPool();
				TaskPool(const TaskPool&) = delete;
				TaskPool(TaskPool&&) = delete;

				~TaskPool();

				//=================================================================================
				// Public Methods
				//=================================================================================
				TaskPool& operator=(const TaskPool&) = delete;
				TaskPool& operator=(TaskPool&&) = delete;

				void	Init(uint aPoolSize);

				Task*	AllocateTask();
				void	FreeTask(Task* aTask);

				Task*	GetTask(TaskId aTaskId);

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
		
				//=================================================================================
				// Private Data
				//=================================================================================
				FreeList<sizeof(Task)>  myTaskFreeList;
				Vector<Task>			myTasks;

				SpinLockMutex			myAllocFreeMutex;
		};
	}
}