#include "Core_Precompile.hpp"
#include "Core_TaskWrapper.hpp"
#include "Core_Task.hpp"

namespace Alba
{
	namespace Core
	{
		uint TaskWrapper::val = 0;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TaskWrapper TaskWrapper::CreateDependentTask(TaskFunction* aTaskFunction)
		{
			(void) aTaskFunction;

			const TaskId id(++val);
			return TaskWrapper{ id };
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TaskWrapper::WaitForAll()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TaskWrapper::QueueTask()
		{

		}

		namespace Internal
		{
			//-----------------------------------------------------------------------------------------
			//-----------------------------------------------------------------------------------------
			Task* CreateTask(Core::TaskFunction* /*aTaskFunction*/)
			{
				return nullptr;
			}

			//-----------------------------------------------------------------------------------------
			//-----------------------------------------------------------------------------------------
			Task* CreateTask(Core::TaskFunction* aTaskFunction, TaskId aParentTask)
			{
				(void) aTaskFunction;
				(void) aParentTask;

				return nullptr;
			}
		}
	}

	//---------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------
	Core::TaskWrapper CreateTask(Core::TaskFunction* /*aTaskFunction*/)
	{
		return Core::TaskWrapper{};
	}
}