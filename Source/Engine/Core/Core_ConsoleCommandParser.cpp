#include "Core_Precompile.hpp"
#include "Core_ConsoleCommandParser.hpp"
#include <cctype>

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ std::tuple<bool, ConsoleCommandParser::ParseState> ConsoleCommandParser::ParseCommandName(ParseState anInputState)
		{
			auto [isValid, commandName] = SkipWhitespace(anInputState);
			if (!isValid)
			{
				return { false, anInputState };
			}

			if (!std::isalpha(commandName.Peek()))
			{
				return { false, anInputState };
			}

			auto match = [](char anInput)
			{
				return std::isalnum(anInput) || anInput == '.' || anInput == '_';
			};

			while (match(commandName.Peek()))
			{
				commandName.Read();
			}

			return { true, commandName };
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ std::tuple<bool, ConsoleCommandParser::ParseState> ConsoleCommandParser::SkipWhitespace(ParseState anInputState)
		{
			ParseState state = anInputState;
			while (!state.IsAtEnd() && (std::isblank(state.Peek()) || std::iscntrl(state.Peek())) )
			{
				state.Skip();
			}

			if (state.IsAtEnd())
			{
				return { false, anInputState };
			}

			state.StartNextToken();
			return { true, state };
		}
	}
}