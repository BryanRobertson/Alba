#pragma once

#include "Core.hpp"
#include "Core_Thread.hpp"
#include "Core_Vector.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_TaskWrapper.hpp"
#include "Core_Array.hpp"
#include "Core_TaskPool.hpp"

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
				// Public Static Methods
				//=================================================================================
				static TaskSystem& GetMutable();

				//=================================================================================
				// Public Methods
				//=================================================================================
				void	Initialise(uint aThreadCount);
				void	Shutdown();

				void	BeginFrame();
				void	EndFrame();

				template <typename... TArgs>
				Task& CreateTask(TArgs&&... someArgs)
				{
					return *myTaskPool.CreateTask(std::forward<TArgs>(someArgs)...);
				}

				void QueueTask(Task& aTask)
				{
					(void) aTask;
				}

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================

				//=================================================================================
				// Private Data
				//=================================================================================
				Vector<thread>	myTaskThreads;
				TaskPool<2048>	myTaskPool;
		};

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		template <typename... TArgs>
		Task& CreateTask(TArgs&&... someArgs)
		{
			TaskSystem& taskSystem = TaskSystem::GetMutable();
			return taskSystem.CreateTask(std::forward<TArgs>(someArgs)...):
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void QueueTask(Task& aTask)
		{
			TaskSystem& taskSystem = TaskSystem::GetMutable();
			taskSystem.QueueTask(aTask);
		}
	}
}