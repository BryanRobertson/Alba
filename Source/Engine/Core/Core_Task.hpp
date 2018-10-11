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

				template <typename TFunctionType>
				Task(TFunctionType&& aTaskFunction)
					: myTaskFunction(aTaskFunction)
				{
					
				}

				template <typename TObjectType>
				Task(TObjectType* anInstance, void (TObjectType::*TaskFunction)(Task&))
					: myTaskFunction(std::bind(anInstance, TaskFunction))
				{

				}

				template <typename TFunctionType>
				Task(Task& aParent, TFunctionType&& aTaskFunction)
					: myTaskFunction(aTaskFunction)
					, myParentTask(&aParent)
				{
					aParent.myOpenTaskCount.fetch_add(1, std::memory_order_relaxed);
				}

				template <typename TObjectType>
				Task(Task& aParent, TObjectType* anInstance, void (TObjectType::*TaskFunction)(Task&))
					: myTaskFunction(std::bind(anInstance, TaskFunction))
					, myParentTask(&aParent)
				{
					aParent.myOpenTaskCount.fetch_add(1, std::memory_order_relaxed);
				}

				Task(const Task&) = delete;
				Task(Task&&) = default;

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
																- sizeof(FixedFunction<void(), 0>);

				static_assert(ourRequiredPaddingSize > 0);

				// Task function - use all remaining size for the function's fixed-size buffer
				FixedFunction<void(Task& aTask), ourRequiredPaddingSize> myTaskFunction;
		};

		// Note: This can be commented out - it doesn't matter if Task is larger than the cache-line size
		//		 I just want to know when it happens
		static_assert(sizeof(Task) == HardwareConstants::theL1CacheLineSize, "sizeof(Task) > cache line size");
	}
}