#include "Core_Precompile.hpp"
#include "Core_TaskWrapper.hpp"
#include "Core_Task.hpp"
#include "Core_TaskSystem.hpp"
#include "Core_TaskIdTypes.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TaskWrapper::TaskWrapper(Task* aTask)
			: myTask(aTask)
		{
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TaskWrapper::~TaskWrapper()
		{
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool TaskWrapper::IsCompleted() const
		{
			if (!myTaskId.IsValid())
			{
				return false;
			}
			
			ALBA_ASSERT(false, "Not Implemented Yet");

			// TODO: Implement
			return false;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TaskPool& TaskWrapper::GetTaskPoolMutable() const
		{
			return TaskSystem::GetTaskPoolMutable(myTaskId);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TaskWrapper TaskWrapper::CreateDependentTask(TaskFunction* aTaskFunction)
		{
			ALBA_ASSERT(myTask);
			ALBA_ASSERT(myTask->myChildTaskCount < Task::ourChildTaskCount);

			const uint32 count = myTask->myChildTaskCount.fetch_add(1, std::memory_order_acq_rel);
			ALBA_ASSERT(count < Task::ourChildTaskCount);

			if (count > Task::ourChildTaskCount)
			{
				myTask->myChildTaskCount.fetch_sub(1, std::memory_order_release);
				return TaskWrapper{};
			}

			// Create child task
			Task* task = TaskSystem::GetMutable().AllocateTask();
			task->myFunction = aTaskFunction;

			// Store task ID in child task array
			myTask->myChildTaskIds[count - 1] = task->myTaskId;

			// Increment open tasks for our task
			myTask->myOpenTasks.fetch_add(1, std::memory_order_release);			

			return TaskWrapper{ task };
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TaskWrapper::WaitForAll()
		{
			ALBA_ASSERT(false, "Not Implemented Yet");
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TaskWrapper::QueueTask()
		{
			ALBA_ASSERT(false, "Not Implemented Yet");
		}
	}

	//---------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------
	Core::TaskWrapper CreateTask(Core::TaskFunction* aTaskFunction)
	{
		using namespace Alba::Core;

		Task* task = TaskSystem::GetMutable().AllocateTask();
		task->myFunction = aTaskFunction;

		return TaskWrapper{ task }
	}
}