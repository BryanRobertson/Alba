#pragma once

#include "Core.hpp"
#include "Core_TaskIdTypes.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_TaskTypes.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------------
		// Name	:	TaskWrapper
		//-----------------------------------------------------------------------------------------------
		struct TaskWrapper
		{
			//===========================================================================================
			// Public Methods
			//===========================================================================================
			
			//-------------------------------------------------------------------------------------------
			// Create
			//-------------------------------------------------------------------------------------------
			TaskWrapper CreateDependentTask(TaskFunction* aTaskFunction);

			template <typename TFunctionType, typename = enable_if_t<is_invocable_v<Core::TaskFunction>>>
			TaskWrapper CreateDependentTask(const TFunctionType& aTask)
			{
				return TaskWrapper{};
			}

			//-------------------------------------------------------------------------------------------
			// Wait
			//-------------------------------------------------------------------------------------------
			void WaitForAll();

			//-------------------------------------------------------------------------------------------
			// Queue
			//-------------------------------------------------------------------------------------------
			void QueueTask();

			//===========================================================================================
			// Public Data
			//===========================================================================================
			TaskId myTaskId;
		};
	}

	//===================================================================================================
	// Functions
	//===================================================================================================
	extern Core::TaskWrapper CreateTask(Core::TaskFunction* aTaskFunction);

	template <typename TFunctionType, typename=enable_if_t<is_invocable_v<Core::TaskFunction>>>
	Core::TaskWrapper CreateTask(const TFunctionType& aTask)
	{
		return Core::TaskWrapper{};
	}
}