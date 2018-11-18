#include "Core_Precompile.hpp"
#include "Core.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_StringHash.hpp"
#include "Core_String.hpp"
#include "Core_CommandLineModule.hpp"
#include "Core_ConsoleModule.hpp"
#include "Core_WindowModule.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void RegisterModules()
		{
			ConsoleModule::Register();
			WindowModule::Register();
		}
	}
}