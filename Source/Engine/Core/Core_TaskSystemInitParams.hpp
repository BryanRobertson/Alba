#pragma once

#include "Core.hpp"
#include "Core_Thread.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		struct TaskSystemInitParams
		{
			uint32	myThreadCount = thread::hardware_concurrency() - 1;
		};
	}
}