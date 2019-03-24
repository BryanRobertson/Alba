#pragma once

#include "Core.hpp"
#include "Core_TaskIdTypes.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_TaskTypes.hpp"
#include "Core_TupleUtils.hpp"

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
			static uint val; // REMOVE_ME

			template <typename TFunctionType, class = enable_if_t<IsTaskFunction_V<TFunctionType>>>
			TaskWrapper CreateDependentTask(TFunctionType&& aTask)
			{
				(void) aTask;
				const TaskId id(++val);

				return TaskWrapper{id};
			}

			template <typename... TArgs>
			auto CreateDependentTasks(TArgs&&... someTaskFunctions)
			{
				auto func = [this](auto&& anArg)
				{
					return CreateDependentTask(std::forward<decltype(anArg)>(anArg));
				};

				return Invoke_ForEach(func, std::forward<TArgs>(someTaskFunctions)...);
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

		namespace Internal
		{
			//-------------------------------------------------------------------------------------------
			// Internal Task-Creation function
			//-------------------------------------------------------------------------------------------
			extern Core::Task* CreateTask(Core::TaskFunction* aTaskFunction);
			extern Core::Task* CreateTask(Core::TaskFunction* aTaskFunction, TaskId aParentTask);
		}
	}

	//===================================================================================================
	// Functions
	//===================================================================================================
	extern Core::TaskWrapper CreateTask(Core::TaskFunction* aTaskFunction);

	template <typename TFunctionType, typename=enable_if_t<is_invocable_v<TFunctionType, Core::TaskFunction>>>
	Core::TaskWrapper CreateTask(const TFunctionType& aTask)
	{
		return Core::TaskWrapper{};
	}
}