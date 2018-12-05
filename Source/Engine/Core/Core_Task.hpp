#pragma once

#include "Core.hpp"
#include "Core_Thread.hpp"
#include "Core_Function.hpp"
#include "Core_Platform.hpp"
#include "Core_TypeTraits.hpp"

namespace Alba
{
	namespace Core
	{
		class Task;

		using TaskFunction = void(Task&);
		using TaskFunctionPtr = TaskFunction*;

		template <typename TObjectType>
		using TaskMemberFunctionPtr = void (TObjectType::*)(Task&);

		template <typename TFunctor>
		using enable_if_taskfunction = enable_if_t<is_invocable_v<TFunctor, TaskFunction>>;
	
		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		class Task
		{
			public:

				friend class TaskSystem;

				//=====================================================================================
				// Public Types
				//=====================================================================================
				
				//=====================================================================================
				// Public Constructors/Destructors
				//=====================================================================================
				Task() = default;

				//-------------------------------------------------------------------------------------
				// Create Task
				//-------------------------------------------------------------------------------------
				template <typename TFunctionType, class=enable_if_taskfunction<TFunctionType> >
				explicit Task(TFunctionType&& aTaskFunction)
					: myTaskFunction(aTaskFunction)
				{

				}

				//-------------------------------------------------------------------------------------
				// Create Task (member function pointer)
				//-------------------------------------------------------------------------------------
				template <typename TObjectType>
				explicit Task(TObjectType* anInstance, TaskMemberFunctionPtr<TObjectType> aMemberFuncPtr)
				{
					myTaskFunction = [anInstance](Task& aTask)
					{
						std::invoke(anInstance, aMemberFuncPtr, aTask);
					};
				}

				//-------------------------------------------------------------------------------------
				// Create Child Task
				//-------------------------------------------------------------------------------------
				template <typename TFunctionType, class=enable_if_taskfunction<TFunctionType> >
				explicit Task(Task& aParent, TFunctionType&& aTaskFunction)
					: Task(aTaskFunction)
					, myParentTask(&aParent)
				{
					myParentTask->myOpenTaskCount.fetch_add(1, std::memory_order_relaxed);
				}

				//-------------------------------------------------------------------------------------
				// Create Child Task (member function pointer)
				//-------------------------------------------------------------------------------------
				template <typename TObjectType>
				explicit Task(Task& aParent, TObjectType* anInstance, TaskMemberFunctionPtr<TObjectType> aMemberFuncPtr)
					: Task(anInstance, aMemberFuncPtr)
					, myParentTask(&aParent)
				{
					myParentTask->myOpenTaskCount.fetch_add(1, std::memory_order_relaxed);
				}

				//-------------------------------------------------------------------------------------
				// Copy / Move Constructors
				//-------------------------------------------------------------------------------------
				Task(const Task&) = delete;
				Task(Task&&) = default;

				//-------------------------------------------------------------------------------------
				// Destructor
				//-------------------------------------------------------------------------------------
				~Task();

				//=====================================================================================
				// Public Methods
				//=====================================================================================

				//-------------------------------------------------------------------------------------
				// Return true if task and all children complete
				//-------------------------------------------------------------------------------------
				bool IsFinished() const
				{
					return myOpenTaskCount.load(std::memory_order_acquire) == 0;
				}

				//-------------------------------------------------------------------------------------
				//-------------------------------------------------------------------------------------
				Task& operator=(Task&) = delete;
				Task& operator=(Task&&) = default;

			private:

				//=====================================================================================
				// Private Methods
				//=====================================================================================

				//-------------------------------------------------------------------------------------
				// Called when the task is run
				//-------------------------------------------------------------------------------------
				void Execute(Task& aTask)
				{
					myTaskFunction(aTask);
					OnFinish();
				}

				//-------------------------------------------------------------------------------------
				// Called when the task finishes
				//-------------------------------------------------------------------------------------
				void OnFinish()
				{
					myOpenTaskCount.fetch_sub(1, std::memory_order_acq_rel);

					if (myParentTask)
					{
						if (myParentTask->myOpenTaskCount.fetch_sub(1, std::memory_order_acq_rel) == 0)
						{
							myParentTask->OnFinish();
						}
					}

					// Clear function
					myTaskFunction = decltype(myTaskFunction)();
				}

				//=====================================================================================
				// Private Data
				//=====================================================================================

				// Parent task
				Task*			myParentTask			= nullptr;

				// Count of tasks that have yet to complete (including ourselves)
				atomic<int32>	myOpenTaskCount			= 1;

				// Keep this up to date: We want sizeof(Task) to take up at least a whole cache-line
				static constexpr int64 ourRequiredPaddingSize = HardwareConstants::theL1CacheLineSize
															  - sizeof(myParentTask)
															  - sizeof(myOpenTaskCount)
															  - sizeof(FixedFunction<TaskFunction, 0>);

				static_assert(ourRequiredPaddingSize > 0);

				// Task function - use all remaining size for the function's fixed-size buffer
				FixedFunction<TaskFunction, ourRequiredPaddingSize> myTaskFunction;

				//=====================================================================================
				// Private Constructors
				//=====================================================================================
				Task(Task* aParent, FixedFunction<TaskFunction, ourRequiredPaddingSize>&& aFunction)
					: myParentTask(aParent)
					, myTaskFunction(aFunction)
				{

				}
		};

		// Note: This can be commented out - it doesn't matter if Task is larger than the cache-line size
		//		 I just want to know when it happens
		static_assert(sizeof(Task) == HardwareConstants::theL1CacheLineSize, "sizeof(Task) > cache line size");
	}
}