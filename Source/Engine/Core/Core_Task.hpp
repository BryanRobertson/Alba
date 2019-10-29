#pragma once

#include "Core_Platform.hpp"
#include "Core_TaskTypes.hpp"
#include "Core_Array.hpp"
#include "Core_AlignedStorage.hpp"
#include "Core_Thread.hpp"
#include "Core_TaskIdTypes.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name : Task
		//-----------------------------------------------------------------------------------------
		struct Task final
		{
			//-----------------------------------------------------------------
			// Function that will be called when the task runs
			//-----------------------------------------------------------------
			TaskFunction*			myFunction	= nullptr;

			//-----------------------------------------------------------------
			// ID of the task
			//-----------------------------------------------------------------
			TaskId					myTaskId	= TaskId::InvalidId;

			//-----------------------------------------------------------------
			// Number of tasks still to run (including ourselves)
			//-----------------------------------------------------------------
			Atomic<uint32>			myOpenTasks	= 1;

			//-----------------------------------------------------------------
			// Storage for the task
			//-----------------------------------------------------------------
			static constexpr uint32 ourStorageSize = HardwareConstants::L1CacheLineSize
													- sizeof(myFunction)
													- sizeof(myTaskId)
													- sizeof(myOpenTasks);

			Core::AlignedStorage<ourStorageSize> myTaskData;

			static constexpr uint32 ourChildTaskCount = 15;

			//-----------------------------------------------------------------
			// Child task IDs
			//-----------------------------------------------------------------
			Array<TaskId, ourChildTaskCount> myChildTaskIds[ourChildTaskCount];
			uint32							 myChildTaskCount;
		};
	}
}