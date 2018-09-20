#include "Input_Precompile.hpp"
#include "Input_Module.hpp"

namespace Alba
{
	namespace Input
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool InputModule::OnLoad(Core::AnyDictionary someLoadParams)
		{
			return myInputService.Init(someLoadParams) == 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void InputModule::OnUnload()
		{
			myInputService.ShutDown();
		}
	}
}