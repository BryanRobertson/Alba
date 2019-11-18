#pragma once

#include "Core_SharedPtr.hpp"

namespace Alba
{
	namespace Core
	{
		struct Task;

		//-----------------------------------------------------------------------------------------
		// Name : TaskPtr
		// Desc : Shared pointer to a task instance, used with a custom deleter
		//		  to return the task to the relevant task pool
		//-----------------------------------------------------------------------------------------
		using TaskPtr = SharedPtr<Task>;
	}
}