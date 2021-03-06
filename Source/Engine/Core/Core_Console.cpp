#include "Core_Precompile.hpp"
#include "Core_Console.hpp"
#include "Core_ConsoleCommandParser.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		Console::Console()
		{
			RegisterInternalCommands();
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		Console::~Console()
		{

		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void Console::Execute(StringView aCommandString)
		{
			Print(ConsoleMessageType::Info, aCommandString);

			//-----------------------------------------------------------------
			// Parse out the command name and try to find it
			//-----------------------------------------------------------------
			ConsoleCommandParser::ParseState parseState { aCommandString };
			const auto [isValid, commandNameToken] = ConsoleCommandParser::ParseCommandName(parseState);

			if (!isValid)
			{
				Print(ConsoleMessageType::Error, "Syntax Error");
				return;
			}

			const StringView commandName = commandNameToken.GetToken();
			const NoCaseStringHash32 commandNameId{ commandName };

			auto itr = myCommands.find(commandNameId);
			if (itr == myCommands.end())
			{
				Print(ConsoleMessageType::Error, "Unrecognised Command: \"%s\"", commandName.data());
				return;
			}

			// Skip the command name so all we have left to parse is the arguments (if the command takes any)
			const StringView argumentString = commandNameToken.GetRemainingInput();

			//-----------------------------------------------------------------
			// We found it! Call the command
			//-----------------------------------------------------------------
			const auto result = itr->second.myVTable->Invoke(itr->second, argumentString);

			//-----------------------------------------------------------------
			// Print result
			//-----------------------------------------------------------------
			if (result != 0)
			{
				Print(ConsoleMessageType::Error, "");
				Print(ConsoleMessageType::Error, "Command \"%s\" returned %u", commandName.data(), result);
				Print(ConsoleMessageType::Error, "");
			}
			else
			{
				Print(ConsoleMessageType::Info, "");
				Print(ConsoleMessageType::Info, "Command \"%s\" returned %u", commandName.data(), 0);
				Print(ConsoleMessageType::Info, "");
			}
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		Console::CommandStorage* Console::InsertCommand(StringView aCommandName)
		{
			const Core::NoCaseStringHash32 commandNameId{ aCommandName };

			ALBA_ASSERT
			(
				myCommands.find(commandNameId) == myCommands.end(),
				"Command %s already registered - existing entry %s",
				aCommandName.data(),
				myCommandNames.find(commandNameId)->second.c_str()
			);

			auto itr = myCommands.emplace(commandNameId, Console::CommandStorage{});
			myCommandNames.emplace(commandNameId, String(aCommandName));

			return &(itr.first->second);
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

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void Console::RegisterInternalCommands()
		{
			using namespace Alba::StringViewLiterals;

			// Register commands that come with the console by default

			//-----------------------------------------------------------------
			// Name	:	cmdlist
			// Desc :	List all registered commands
			//-----------------------------------------------------------------
			RegisterCommand("cmdlist", [this]() -> int
			{
				PrintInfo(""sv);
				PrintInfo("-------------"sv);
				PrintInfo("Command List:"sv);
				PrintInfo("-------------"sv);

				for (auto& command : myCommandNames)
				{
					Print(ConsoleMessageType::Info, "    %s"sv, command.second.data());
				}

				return 0;
			});

			//-----------------------------------------------------------------
			// Name :	help
			// Desc :	Print help text to the console
			//-----------------------------------------------------------------
			RegisterCommand("help", [this]() -> int
			{
				PrintInfo("-------------"sv);
				PrintInfo("Help"sv);
				PrintInfo("-------------"sv);

				PrintInfo("Type cmdlist for a list of valid commands"sv);
				PrintInfo(""sv);
				PrintInfo("-------------"sv);
				PrintInfo("Command List:"sv);
				PrintInfo("-------------"sv);

				for (auto& command : myCommandNames)
				{
					Print(ConsoleMessageType::Info, "    %s"sv, command.second.data());
				}

				return 0;
			});
		}
	}
}
