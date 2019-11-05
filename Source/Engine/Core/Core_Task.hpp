#pragma once

#include "Core_Platform.hpp"
#include "Core_TaskTypes.hpp"
#include "Core_Array.hpp"
#include "Core_AlignedStorage.hpp"
#include "Core_Thread.hpp"
#include "Core_EnumerationSet.hpp"
#include "Core_TaskIdTypes.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*
		enum class TaskFlag : uint8 
		{
			None,

			// Traits
			enum_traits_start_value = None,
			enum_traits_end_value = None + 1,
			enum_traits_is_contiguous = 1
		};

		using TaskFlags = EnumerationSet<TaskFlag>;
		*/

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
													- sizeof(myOpenTasks)
													- sizeof(Atomic<uint32>); // Last uint32 is for reference count;

			Core::AlignedStorage<ourStorageSize> myTaskData;

			//-----------------------------------------------------------------
			// Ensure that we don't delete the task while
			// someone is holding onto a pointer to it
			//-----------------------------------------------------------------
			Atomic<uint32>			myReferenceCount = 1;

			static constexpr uint32 ourChildTaskCount = 13;

			//-----------------------------------------------------------------
			// Child task IDs
			//
			// The task is considered completed when it and all child tasks
			// are completed
			//-----------------------------------------------------------------
			Array<TaskId, ourChildTaskCount> myChildTaskIds;
			Atomic<uint32>					 myChildTaskCount;

			//-----------------------------------------------------------------
			// Next task ID
			// The next task is started after the task and all child tasks
			// are completed.
			//
			// Useful for cases where you want to do something like 
			// lock the scene graph mutex on starting the task and then
			// unlock it when all tasks are completed
			//-----------------------------------------------------------------
			Atomic<TaskId>					 myNextTask;
		};
	}
}