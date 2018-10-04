#include "Core_Precompile.hpp"
#include "Core_TaskSystemModule.hpp"
#include "Core_Thread.hpp"
#include "Core_TaskSystemInitParams.hpp"
#include "Core_TaskDebug.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool TaskSystemModule::OnLoad(Core::AnyDictionary someParameters)
		{
			TaskSystemInitParams initParams;
			if (someParameters.Has<TaskSystemInitParams>())
			{
				initParams = someParameters.Get<TaskSystemInitParams>();
			}
			
			myTaskSystem.Initialise(initParams.myThreadCount);

			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TaskSystemModule::OnUnload()
		{
			myTaskSystem.Shutdown();
		}
	}
}