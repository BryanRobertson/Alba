#pragma once

#include "Core_Platform.hpp"
#include "Core_TaskTypes.hpp"
#include "Core_Any.hpp"
#include "Core_AlignedStorage.hpp"
#include "Core_Thread.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name : Task
		// Desc : 
		//-----------------------------------------------------------------------------------------
		struct alignas(HardwareConstants::theL1CacheLineSize) Task final
		{
			std::atomic<uint32>			myOpenTasks;
			

			Core::AlignedStorage<32>	myTaskData;
		};
	}
}