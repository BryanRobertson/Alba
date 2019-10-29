#pragma once

#include "Core.hpp"
#include "Core_TaskTypes.hpp"
#include "Core_TaskIdTypes.hpp"
#include "Core_Task.hpp"
#include "Core_TaskPtr.hpp"

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

				void Init(TaskThreadId aThreadId);

				TaskPtr AllocateTask(TaskId aTaskId);
				void FreeTask(Task* aTask);

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				TaskThreadId myThreadId;
		};
	}
}