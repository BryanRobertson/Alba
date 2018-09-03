#include "Core_Precompile.hpp"
#include "Core_ConsoleModule.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool ConsoleModule::OnLoad(Core::AnyDictionary /*someParameters*/)
		{
			myConsole.reset(ALBA_NEW(AllocationType::Module, "ConsoleModule") Console());
			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ConsoleModule::OnUnload()
		{
			myConsole.reset();
		}
	}
}