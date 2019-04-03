#pragma once

#include "Core.hpp"
#include "Core_TaskIdTypes.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_TaskTypes.hpp"
#include "Core_Task.hpp"
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

			template <typename TFunctionType, class = enable_if_t<IsTaskFunction_V<TFunctionType>>>
			TaskWrapper CreateDependentTask(TFunctionType&& /*aTask*/)
			{
				const TaskId id;
				return TaskWrapper{ id };
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
			TaskId	myTaskId;
			Task*	myTask = nullptr;
		};
	}

	//===================================================================================================
	// Functions
	//===================================================================================================
	extern Core::TaskWrapper CreateTask(Core::TaskFunction* aTaskFunction);

	//---------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------
	template <typename TFunctionType, typename=enable_if_t<is_invocable_v<TFunctionType, Core::TaskFunction>>>
	Core::TaskWrapper CreateTask(const TFunctionType& aTask)
	{
		auto taskFunc = [](const Core::TaskExecutionContext& aContext)
		{
			// Call function
			TFunctionType* func = reinterpret_cast<TFunctionType*>(&aContext.myTask.myTaskData.mCharData);
			(func)(aContext);

			// Destruct task data
			func->~TFunctionType();
		};

		return Core::TaskWrapper{};
	}
}