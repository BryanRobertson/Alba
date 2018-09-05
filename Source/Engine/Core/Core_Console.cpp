#include "Core_Precompile.hpp"
#include "Core_Console.hpp"

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
		void Console::UnregisterCommand(NoCaseStringHash32 aCommandName)
		{
			(void)aCommandName;
			//myConsoleCommands.erase(aCommandName);
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
