#include "Core_Precompile.hpp"
#include "Core_TaskWrapper.hpp"
#include "Core_Task.hpp"
#include "Core_TaskSystem.hpp"

namespace Alba
{
	namespace Core
	{
		/*static*/ uint32 TaskWrapper::ourTaskIdCounter = 0;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ TaskId TaskWrapper::CreateTaskId()
		{
			const uint8 threadId = static_cast<uint8>(TaskSystem::GetCurrentThreadId().GetValue());
			const uint32 id = (threadId << 24) | (++ourTaskIdCounter & 0xFFFFFF);

			return TaskId(id);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TaskWrapper TaskWrapper::CreateDependentTask(TaskFunction* aTaskFunction)
		{
			(void) aTaskFunction;

			const TaskId id = CreateTaskId();
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