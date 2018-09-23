#include "Core_Precompile.hpp"
#include "Core.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_StringHash.hpp"
#include "Core_String.hpp"
#include "Core_CommandLineModule.hpp"
#include "Core_ConsoleModule.hpp"
#include "Core_WindowModule.hpp"
#include "Core_TaskSystemModule.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void RegisterModules()
		{
			TaskSystemModule::Register();
			ConsoleModule::Register();
			WindowModule::Register();
		}
	}
}