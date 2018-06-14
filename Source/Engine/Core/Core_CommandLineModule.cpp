#include "Core_Precompile.hpp"
#include "Core_CommandLineModule.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void CommandLineModule::OnRegister()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void CommandLineModule::OnUnregister()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool CommandLineModule::OnLoad(Core::AnyDictionary someParams)
		{
			if (someParams.Has<Core::CommandLineParameters>())
			{
				Core::CommandLineParameters& commandLine = someParams.GetMutable<Core::CommandLineParameters>();
				myCommandLineParameters = std::move(commandLine);
			}

			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void CommandLineModule::OnUnload()
		{
			
		}
	}
}