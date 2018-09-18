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
			(void)someLoadParams;
			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void InputModule::OnUnload()
		{

		}
	}
}