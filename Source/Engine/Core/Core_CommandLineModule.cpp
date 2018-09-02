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
			ALBA_LOG_INFO(Module, "---------------------------");
			ALBA_LOG_INFO(Module, "CommandLineModule - OnLoad");
			ALBA_LOG_INFO(Module, "---------------------------");

			if (someParams.Has<Core::CommandLineParameters>())
			{
				Core::CommandLineParameters& commandLine = someParams.GetMutable<Core::CommandLineParameters>();
				myCommandLineParameters = std::move(commandLine);

				#if defined(ALBA_DEBUG_LOGGING_ENABLED)
				{
					myCommandLineParameters.ForEach_Param([](NoCaseStringHash32 aNameId, StringView aValue)
					{
						ALBA_LOG_INFO(Module, "\"%s\" = \"%s\"", aNameId.LogString().c_str(), aValue.data());
					});
				}
				#endif
			}

			ALBA_LOG_INFO(Module, "---------------------------");

			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void CommandLineModule::OnUnload()
		{
			
		}
	}
}