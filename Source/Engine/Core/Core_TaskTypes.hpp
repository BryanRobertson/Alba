#pragma once

#include "Core_TaskTypes.hpp"

namespace Alba
{
	namespace Core
	{
		struct Task;

		//-----------------------------------------------------------------------------------------
		// Name	:	TaskExecutionContext
		// Desc :	Input Data that's passed to a task execution function
		//-----------------------------------------------------------------------------------------
		struct TaskExecutionContext
		{
			Task& myTask;
		};

		//-----------------------------------------------------------------------------------------
		// Task function
		//-----------------------------------------------------------------------------------------
		using TaskFunction = void(TaskExecutionContext& aTask);
	}
}