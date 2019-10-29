#pragma once

#include "Core.hpp"
#include "Core_TaskIdTypes.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_TaskTypes.hpp"
#include "Core_Task.hpp"
#include "Core_TaskPtr.hpp"
#include "Core_TupleUtils.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------------
		// Name	:	TaskWrapper
		//-----------------------------------------------------------------------------------------------
		class TaskWrapper
		{
			public:

				//===========================================================================================
				// Public Constructors
				//===========================================================================================
				TaskWrapper() = default;
				TaskWrapper(const TaskWrapper&) = delete;
				TaskWrapper(TaskWrapper&&) = default;

				//===========================================================================================
				// Public Methods
				//===========================================================================================
				TaskWrapper& operator=(const TaskWrapper&) = delete;
				TaskWrapper& operator=(TaskWrapper&&) = default;
			
				//-------------------------------------------------------------------------------------------
				// Create
				//-------------------------------------------------------------------------------------------
				TaskWrapper CreateDependentTask(TaskFunction* aTaskFunction);

				template <typename TFunctionType, class = enable_if_t<IsTaskFunction_V<TFunctionType>>>
				TaskWrapper CreateDependentTask(TFunctionType&& /*aTask*/)
				{
					const TaskId id;
					return TaskWrapper();//{ id };
				}

				template <typename... TArgs>
				auto CreateDependentTasks(TArgs&&... someTaskFunctions)
				{
					static_assert
					(
						sizeof...(someTaskFunctions) <= Task::ourChildTaskCount,
						"Exceeding the max number of child tasks is not yet supported"
					);

					//ALBA_ASSERT()

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

				//-------------------------------------------------------------------------------------------
				// Accessors
				//-------------------------------------------------------------------------------------------
				inline TaskId GetTaskId() const;

			private:

				//===========================================================================================
				// Private Data
				//===========================================================================================
				TaskPtr	myTask;
				TaskId	myTaskId;
		};

		//---------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------
		TaskId TaskWrapper::GetTaskId() const
		{
			return myTaskId;
		}
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
		// TODO: Probably need to account for alignment here
		static_assert(sizeof(aTask) < Task::ourStorageSize, "Functor too large to store in a Task");

		auto taskFunc = [](const Core::TaskExecutionContext& aContext)
		{
			// Call function
			TFunctionType* func = reinterpret_cast<TFunctionType*>(&aContext.myTask.myTaskData.mCharData);
			(func)(aContext);

			// Destruct task data
			func->~TFunctionType();
		};

		return CreateTask(static_cast<Core::TaskFunction*>(&taskFunc));
	}
}