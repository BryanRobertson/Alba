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
		class TaskPool;

		//-----------------------------------------------------------------------------------------------
		// Name	:	TaskWrapper
		//-----------------------------------------------------------------------------------------------
		class TaskWrapper
		{
			public:

				//===========================================================================================
				// Public Constructors/Destructors
				//===========================================================================================
				TaskWrapper() = default;
				TaskWrapper(const TaskWrapper&) = delete;
				TaskWrapper(TaskWrapper&&) = default;

				explicit TaskWrapper(Task* aTask);

				~TaskWrapper();

				//===========================================================================================
				// Public Methods
				//===========================================================================================
				TaskWrapper& operator=(const TaskWrapper&) = delete;
				TaskWrapper& operator=(TaskWrapper&&) = default;

				bool IsCompleted() const;
			
				//-------------------------------------------------------------------------------------------
				// Create
				//-------------------------------------------------------------------------------------------

				//-------------------------------------------------------------------------------------------
				//-------------------------------------------------------------------------------------------
				TaskWrapper CreateDependentTask(TaskFunction* aTaskFunction);

				//-------------------------------------------------------------------------------------------
				//-------------------------------------------------------------------------------------------
				template <typename TFunctionType, class = enable_if_t<IsTaskFunction_V<TFunctionType>>>
				inline TaskWrapper CreateDependentTask(TFunctionType&& aTask);

				//-------------------------------------------------------------------------------------------
				//-------------------------------------------------------------------------------------------
				template <typename... TArgs>
				auto CreateDependentTasks(TArgs&&... someTaskFunctions)
				{
					static_assert
					(
						sizeof...(someTaskFunctions) <= Task::ourChildTaskCount,
						"Exceeding the max number of child tasks is not yet supported"
					);

					auto func = [this](auto&& anArg)
					{
						return CreateDependentTask(std::forward<decltype(anArg)>(anArg));
					};

					return Invoke_ForEach(func, std::forward<TArgs>(someTaskFunctions)...);
				}

				//-------------------------------------------------------------------------------------------
				//-------------------------------------------------------------------------------------------
				TaskWrapper Then(TaskFunction* aTaskFunction)
				{
					ALBA_ASSERT(myTask);					
					TaskWrapper taskWrapper = CreateTask(aTaskFunction);

					if (taskWrapper.myTaskId.IsValid())
					{
						TaskId invalid(TaskId::InvalidId);

						const bool result = myTask->myNextTask.compare_exchange_strong
						(
							invalid,
							taskWrapper.myTaskId, 
							std::memory_order_acq_rel
						);

						ALBA_ASSERT(result);

						if (!result)
						{
							
						}
					}

					return taskWrapper;
				}

				//-------------------------------------------------------------------------------------------
				//-------------------------------------------------------------------------------------------
				template <typename TFunctionType, class = enable_if_t<IsTaskFunction_V<TFunctionType>>>
				TaskWrapper Then(TaskFunction* /*aTaskFunction*/)
				{
					return TaskWrapper();
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
				// Private Methods
				//===========================================================================================
				TaskPool& GetTaskPoolMutable() const;

				Core::TaskWrapper CreateTask(Core::TaskFunction* aTaskFunction);

				//===========================================================================================
				// Private Data
				//===========================================================================================
				Task*	myTask		= nullptr;
				TaskId	myTaskId	= TaskId::InvalidId;
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
	Core::TaskWrapper CreateTask(TFunctionType&& aTask)
	{
		static_assert(sizeof(aTask) < Task::ourStorageSize, "Functor too large to store in a Task");

		auto taskFunc = [](const Core::TaskExecutionContext& aContext)
		{
			// Call function
			TFunctionType* func = reinterpret_cast<TFunctionType*>(&aContext.myTask.myTaskData.mCharData);
			(func)(aContext);

			// Destruct task data
			func->~TFunctionType();
		};

		Core::TaskWrapper taskWrapper = CreateTask(static_cast<Core::TaskFunction*>(&taskFunc));
		if (taskWrapper.myTask)
		{
			new (&taskWrapper.myTask->myTaskData.mCharData)TFunctionType(std::move(aTask));
		}

		return taskWrapper;
	}

	//---------------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------------
	template <typename TFunctionType, typename>
	inline Core::TaskWrapper Core::TaskWrapper::CreateDependentTask(TFunctionType&& aTask)
	{
		static_assert(sizeof(aTask) < Task::ourStorageSize, "Functor too large to store in a Task");

		auto taskFunc = [](const Core::TaskExecutionContext& aContext)
		{
			// Call function
			TFunctionType* func = reinterpret_cast<TFunctionType*>(&aContext.myTask.myTaskData.mCharData);
			(*func)(aContext);

			// Destruct task data
			func->~TFunctionType();
		};

		Core::TaskFunction* taskFunction(taskFunc);

		Core::TaskWrapper taskWrapper = CreateDependentTask(taskFunction);
		if (taskWrapper.myTask)
		{
			new (&taskWrapper.myTask->myTaskData.mCharData)TFunctionType(std::move(aTask));
		}

		return taskWrapper;
	}
}