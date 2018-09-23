#include "Core_Precompile.hpp"
#include "Core_TaskSystemModule.hpp"
#include "Core_Thread.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool TaskSystemModule::OnLoad(Core::AnyDictionary /*someParameters*/)
		{
			const uint hardwareThreads = thread::hardware_concurrency();
			myTaskSystem.Initialise(hardwareThreads - 1);

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