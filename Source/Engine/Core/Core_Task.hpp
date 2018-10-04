#pragma once

#include "Core.hpp"
#include "Core_Thread.hpp"
#include "Core_Function.hpp"
#include "Core_Platform.hpp"

namespace Alba
{
	namespace Core
	{
		typedef void(*TaskFunction)(Task& aTask);

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		class Task
		{
			public:

				//=====================================================================================
				// Public Types
				//=====================================================================================
				
				//=====================================================================================
				// Public Constructors/Destructors
				//=====================================================================================
				Task() = default;
				Task(TaskFunction aTaskFunction);
				Task(Task& aParent, TaskFunction aTaskFunction);

				Task(const Task&) = delete;
				Task(Task&&) = default;

				~Task();

				//=====================================================================================
				// Public Methods
				//=====================================================================================

				//-------------------------------------------------------------------------------------
				// Called when the task is run
				//-------------------------------------------------------------------------------------
				void Run()
				{
					myTaskFunction(*this);
					OnFinish();
				}

				bool IsFinished() const
				{
					return myOpenChildCount.load(std::memory_order_acquire) == 0;
				}

			private:

				//=====================================================================================
				// Private Methods
				//=====================================================================================

				//-------------------------------------------------------------------------------------
				// Called when the task finishes
				//-------------------------------------------------------------------------------------
				void OnFinish()
				{
					myOpenChildCount.fetch_sub(1, std::memory_order_acq_rel);

					if (myParentTask)
					{
						if (myParentTask->myOpenChildCount.fetch_sub(1, std::memory_order_acq_rel) == 0)
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
				Task*			myParentTask		= nullptr;

				// Count of tasks that have yet to complete (including ourselves)
				atomic<uint32>	myOpenChildCount	= 1;

				// Keep this up to date: We want sizeof(Task) to take up at least a whole cache-line
				static constexpr int64 ourRequiredPaddingSize = HardwareConstants::theL1CacheLineSize
																- sizeof(myParentTask)
																- sizeof(myOpenChildCount)
																- sizeof(FixedFunction<void(), 0>);

				static_assert(ourRequiredPaddingSize > 0);

				// Task function - use all remaining size for the function's fixed-size buffer
				FixedFunction<void(Task&), ourRequiredPaddingSize> myTaskFunction;
		};

		// Note: This can be commented out - it doesn't matter if Task is larger than the cache-line size
		//		 I just want to know when it happens
		static_assert(sizeof(Task) == HardwareConstants::theL1CacheLineSize, "sizeof(Task) > cache line size");
	}
}