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
		bool CommandLineModule::OnLoad(const Core::AnyDictionary& someParams)
		{
			if (someParams.Has<Core::String>())
			{
				const Core::String& commandLine = someParams.Get<Core::String>();
				myCommandLineParameters.Init(commandLine.c_str());
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