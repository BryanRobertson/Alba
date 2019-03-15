#pragma once

#include "Core_Platform.hpp"
#include "Core_TaskTypes.hpp"
#include "Core_Any.hpp"
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
		struct alignas(HardwareConstants::L1CacheLineSize) Task final
		{
			TaskFunction*				myFunction	= nullptr;
			TaskId						myTaskId	= TaskId::InvalidId;
			TaskId						myParentId	= TaskId::InvalidId;
			std::atomic<uint32>			myOpenTasks	= 1;

			static constexpr size_t ourStorageSize = HardwareConstants::L1CacheLineSize
													- sizeof(myFunction)
													- sizeof(myTaskId)
													- sizeof(myParentId)
													- sizeof(myOpenTasks);

			Core::AlignedStorage<ourStorageSize> myTaskData;
		};
	}
}