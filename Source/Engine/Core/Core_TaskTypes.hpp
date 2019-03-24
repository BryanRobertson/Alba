#pragma once

#include "Core_TaskTypes.hpp"
#include "Core_TypeTraits.hpp"

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
			Task&			myTask;
			TaskThreadId	myExecutionThreadId;
		};

		//-----------------------------------------------------------------------------------------
		// Task function
		//-----------------------------------------------------------------------------------------
		using TaskFunction = void(const TaskExecutionContext&);

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TFunc>
		using IsTaskFunction = is_invocable<TFunc, const TaskExecutionContext&>;

		template <typename TFunc>
		static constexpr bool IsTaskFunction_V = IsTaskFunction<TFunc>::value;
	}
}