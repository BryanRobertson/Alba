#pragma once

#include "Core.hpp"
#include "Core_Thread.hpp"
#include "Core_Array.hpp"
#include "Core_Task.hpp"
#include "Core_AlignedStorage.hpp"
#include "Core_Platform.hpp"

namespace Alba
{
	namespace Core
	{
		class Task;

		//-----------------------------------------------------------------------------------------
		// Name	:	TaskPool
		// Desc	:	Represents a global fixed-size pool of task instances stored as a circular buffer
		//			As tasks are allocated, the buffer will eventually wrap around
		//			so a large enough size must be chosen to ensure that we don't overwrite tasks
		//			that are in progress
		//-----------------------------------------------------------------------------------------
		class TaskPool final
		{
			public:

				//================================================================================
				// Public Types
				//================================================================================
				using TaskStorage = AlignedStorageT<Task>;

				//================================================================================
				// Public Constructors / Destructors
				//================================================================================
				TaskPool();
				~TaskPool();

				//================================================================================
				// Public Methods
				//================================================================================
				void	Reset();

				//--------------------------------------------------------------------------------
				// Allocate/Deallocate Task
				//--------------------------------------------------------------------------------
				void*	AllocateTask();
				void	DeallocateTask(Task& aTask);

			private:

				//================================================================================
				// Private Static Constants
				//================================================================================
				static constexpr size_t ourTaskPoolSize = 4096;

				//================================================================================
				// Private Types
				//================================================================================
				using TaskStorageArray = Array<TaskStorage, ourTaskPoolSize>;

				//================================================================================
				// Private Methods
				//================================================================================
				
				//================================================================================
				// Private Data
				//================================================================================
				TaskStorageArray	myTaskStorage;
				uint32				myNextFreeTaskIndex = 0;
				uint32				myOpenTaskCount = 0;
		};
	}
}