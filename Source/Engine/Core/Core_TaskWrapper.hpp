#pragma once

#include "Core.hpp"
#include "Core_Thread.hpp"
#include "Core_Function.hpp"
#include "Core_Platform.hpp"
#include "Core_Task.hpp"
#include "Core_TaskSystem.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		class TaskSystem;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		class TaskWrapper
		{
		public:

			TaskWrapper StartChild(TaskFunction /*aTaskFunction*/)
			{
				//myTaskSystem->CreateTask(*myTask, aTaskFunction);
			}

			TaskWrapper Then(TaskFunction /*aTaskFunction*/)
			{
				//myTaskSystem->CreateTask(*myTask, aTaskFunction);
			}

			void WaitFor()
			{
				//myTaskSystem->WaitFor(*myTask);
			}

			Task*		myTask = nullptr;
			TaskSystem* myTaskSystem = nullptr;
		};
	}
}
