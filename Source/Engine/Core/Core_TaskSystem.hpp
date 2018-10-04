#pragma once

#include "Core.hpp"
#include "Core_Thread.hpp"
#include "Core_Task.hpp"
#include "Core_Vector.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_Array.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	TaskSystem
		// Desc	:	Multithreaded task system, executes a tree of tasks over several threads
		//-----------------------------------------------------------------------------------------
		class TaskSystem final
		{
			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				TaskSystem();
				~TaskSystem();

				//=================================================================================
				// Public Methods
				//=================================================================================
				void	Initialise(uint aThreadCount);
				void	Shutdown();

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				bool IsTaskPoolFull() const
				{
					return myNextFreeTaskIndex.load(std::memory_order_acquire) >= myTaskPool.size();
				}
				
				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				template <typename TFunctor, class = enable_if_t<is_invocable_v<TFunctor, void()>> >
				Task& AllocateTask(TFunctor&& aFunctor)
				{
					const uint32 index = myNextFreeTaskIndex.fetch_add(1, std::memory_order_relaxed);
					ALBA_ASSERT(index < myTaskPool.size());

					Task& task = myTaskPool[(index - 1) & (ourMaxTasks - 1)];
					task.myId = index;
					task.myOpenChildCount.store(1, std::memory_order_relaxed);
					task.myTaskFunction = std::move(aFunctor);

					return task;
				}

				//=================================================================================
				// Private Data
				//=================================================================================
				Vector<thread>	myFrameTaskThreads;
				Vector<thread>	myMultiFrameTaskThreads;

				// Note: ourMaxTasks must be a power of two
				static const size_t ourMaxTasks = 2048;
				Array<Task, ourMaxTasks>	myTaskPool;

				// Task index is never reset, we use the value % ourMaxTasks
				atomic<uint32>	myNextFreeTaskIndex = 0u;
		};
	}
}