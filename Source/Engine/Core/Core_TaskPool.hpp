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
				// Public Static Methods
				//================================================================================
				static void Init();

				//--------------------------------------------------------------------------------
				//--------------------------------------------------------------------------------
				template <typename... TArgs>
				static Task* CreateTask(TArgs&&... someArgs)
				{
					TaskStorage* taskStorage = AllocateTask();
					new (taskStorage) Task(std::forward<TArgs>(someArgs)...);
				}

				//--------------------------------------------------------------------------------
				//--------------------------------------------------------------------------------
				static void DestructTask(Task& aTask)
				{
					TaskStorage* storage = reinterpret_cast<TaskStorage*>(&aTask);
					aTask.~Task();

					DeallocateTask(storage);
				}

			private:

				//================================================================================
				// Private Methods
				//================================================================================
				static TaskStorage*		AllocateTask();
				static void				DeallocateTask(TaskStorage* aStorage);
		};
	}
}