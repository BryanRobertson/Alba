#include "Input_Precompile.hpp"
#include "Input.hpp"
#include "Input_Module.hpp"

namespace Alba
{
	namespace Input
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void RegisterModules()
		{
			InputModule::Register();
		}
	}
}