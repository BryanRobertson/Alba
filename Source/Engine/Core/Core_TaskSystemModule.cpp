#include "Core_Precompile.hpp"
#include "Core_TaskSystemModule.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool TaskSystemModule::OnLoad(Core::AnyDictionary /*someParameters*/)
		{
			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TaskSystemModule::OnUnload()
		{
			myThreadPool.Stop();
		}
	}
}