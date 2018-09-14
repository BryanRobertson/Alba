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
		void Console::RegisterInternalCommands()
		{
			using namespace Alba::StringViewLiterals;

			//-----------------------------------------------------------------
			// Name	:	cmdlist
			// Desc :	List all registered commands
			//-----------------------------------------------------------------
			RegisterCommand("cmdlist", [this]() -> CommandReturnCode
			{
				Print(ConsoleMessageType::Info, "Command List:"sv);
				Print(ConsoleMessageType::Info, "-------------"sv);

				for (auto& command : myCommandNames)
				{
					Print(ConsoleMessageType::Info, "    %s"sv, command.second.data());
				}

				return 0;
			});
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void Console::Execute(StringView aCommandString)
		{
			Print(ConsoleMessageType::Info, aCommandString);

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
			}
			else
			{
				Print(ConsoleMessageType::Info, "Command - \"%s\"", aCommandString.data());
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
	}
}
