#include "Core_Precompile.hpp"
#include "Core_Task.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Task::Task(TaskFunction aTaskFunction)
			: myTaskFunction(aTaskFunction)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Task::Task(Task& aParent, TaskFunction aTaskFunction)
			: myTaskFunction(aTaskFunction)
			, myParentTask(&aParent)
		{
			myParentTask->myOpenChildCount.fetch_add(1, std::memory_order_relaxed);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Task::~Task()
		{
			ALBA_ASSERT(IsFinished(), "Aborting task before it has completed!");
		}
	}
}
