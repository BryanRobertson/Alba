#include "Core_Precompile.hpp"
#include "Core_TaskWrapper.hpp"
#include "Core_Task.hpp"
#include "Core_TaskSystem.hpp"
#include "Core_TaskIdTypes.hpp"

namespace Alba
{
	namespace Core
	{
		static uint32 ourTaskIdCounter = 0;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		static TaskId CreateTaskId()
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

			//const TaskId id = CreateTaskId();
			return TaskWrapper(); // { id };
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
	}

	//---------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------
	Core::TaskWrapper CreateTask(Core::TaskFunction* /*aTaskFunction*/)
	{
		const Core::TaskId id = Core::CreateTaskId();
		return Core::TaskWrapper{};
	}
}