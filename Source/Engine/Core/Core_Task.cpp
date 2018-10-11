#include "Core_Precompile.hpp"
#include "Core_Task.hpp"
#include "Core_TaskSystemModule.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Task::~Task()
		{
			ALBA_ASSERT(IsFinished(), "Aborting task before it has completed!");
		}
	}
}
