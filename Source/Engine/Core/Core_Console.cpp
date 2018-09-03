#include "Core_Precompile.hpp"
#include "Core_Console.hpp"
#include "Core_ConsoleCommand.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		Console::Console()
		{

		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		Console::~Console()
		{

		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void Console::RegisterCommand(ConsoleCommand& aCommand)
		{
			ALBA_ASSERT(myConsoleCommands.find(aCommand.GetNameId()) == myConsoleCommands.end(), "Command %s is already registered!", aCommand.GetName());
			myConsoleCommands.emplace(aCommand.GetNameId(), &aCommand);
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void Console::UnregisterCommand(NoCaseStringHash32 aCommandName)
		{
			myConsoleCommands.erase(aCommandName);
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void Console::Execute(StringView /*aCommandString*/)
		{
			
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void Console::Print(ConsoleMessageType aMessageType, StringView aStr)
		{
			for (const auto& callback : myPrintCallbacks)
			{
				callback.second(aMessageType, aStr);
			}
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		Console::PrintCallbackId Console::RegisterPrintCallback(const Console::PrintCallback& aCallback)
		{
			static uint32 nextFreeId = 1;
			const PrintCallbackId id(nextFreeId);

			myPrintCallbacks.emplace(id, aCallback);

			return id;
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void Console::UnregisterPrintCallback(Console::PrintCallbackId anId)
		{
			myPrintCallbacks.erase(anId);
		}
	}
}
