#pragma once

#include "Core.hpp"
#include "Core_Thread.hpp"
#include "Core_Vector.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_Array.hpp"
#include "Core_UniquePtr.hpp"
#include "Core_TaskWorker.hpp"
#include "Core_TaskPool.hpp"
#include "Core_TaskIdTypes.hpp"

namespace Alba
{
	namespace Core
	{
		struct Task;

		//-----------------------------------------------------------------------------------------
		// Name	:	TaskSystem
		// Desc	:	Multithreaded task system, executes a tree of tasks over several threads
		//-----------------------------------------------------------------------------------------
		class TaskSystem final
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static void			Initialise(Optional<uint> aThreadCount=nullopt);
				static void			Shutdown();
				static TaskSystem&	GetMutable();

				static void			QueueTask(Task& aTask);

				static TaskPool&	GetCurrentThreadTaskPool();

				static TaskPool&	GetTaskPoolMutable(TaskId aTaskId);
				static TaskPool&	GetTaskPoolMutable(TaskThreadId aTaskThreadId);

				static TaskThreadId GetOriginatingThreadId(TaskId aTaskId);

				static TaskThreadId	GetCurrentThreadId();
				static TaskThreadId GetMainThreadId();

				//=================================================================================
				// Public Constructors
				//=================================================================================
				TaskSystem();
				~TaskSystem();
		
				//=================================================================================
				// Public Methods
				//================================================================================
				void				BeginFrame();
				void				EndFrame();
				Task*				AllocateTask();

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				void				InitialiseInternal(uint aThreadCount);
				void				ShutdownInternal();

				//=================================================================================
				// Private Data
				//=================================================================================
				TaskPool*			myTaskPools		= nullptr;
				TaskWorker*			myTaskWorkers	= nullptr;
				uint				myThreadCount	= 0;
		};

		#if 0

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		inline void QueueTask(Task& aTask)
		{
			TaskSystem& taskSystem = TaskSystem::GetMutable();
			taskSystem.QueueTask(aTask);
		}

		#endif
	}
}