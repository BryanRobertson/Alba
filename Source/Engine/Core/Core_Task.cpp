#include "Core_Precompile.hpp"
#include "Core_Task.hpp"

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
