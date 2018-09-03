#include "Graphics_Precompile.hpp"
#include "Graphics_ConsoleModule.hpp"
#include "Graphics_Console.hpp"
#include "Graphics_Debug.hpp"

#include "Core_ConsoleModule.hpp"
#include "Core_Memory.hpp"

namespace Alba
{
	namespace Graphics
	{
		using namespace Alba::BasicTypes;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool ConsoleModule::OnLoad(Core::AnyDictionary /*someParameters*/)
		{
			// Get console backend
			Core::ConsoleModule& consoleModule = Core::ConsoleModule::Get();
			if (!consoleModule.IsLoaded())
			{
				ALBA_LOG_ERROR(Graphics, "Failed to load console module - console back-end is not loaded!");
				return false;
			}

			// Create console front-end
			{
				myConsole.reset(ALBA_NEW(Core::AllocationType::Module, "Graphical Console") Console());
			}

			// Hook front-end up to back-end
			{
				Core::Console& consoleBackend = consoleModule.GetConsole();
				myPrintCallbackId = consoleBackend.RegisterPrintCallback([this](Alba::Core::ConsoleMessageType aMessageType, Alba::Core::StringView aMessage)
				{
					myConsole->Print(aMessageType, aMessage);
				});
			}

			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ConsoleModule::OnUnload()
		{
			// Get console backend
			Core::ConsoleModule& consoleModule = Core::ConsoleModule::Get();
			if (consoleModule.IsLoaded() && myPrintCallbackId.IsValid())
			{
				consoleModule.GetConsole().UnregisterPrintCallback(myPrintCallbackId);
				myPrintCallbackId = Core::Console::PrintCallbackId::InvalidId;
			}

			myConsole.reset();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ConsoleModule::Render()
		{
			myConsole->Render();
		}
	}
}