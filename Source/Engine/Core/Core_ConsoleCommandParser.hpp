#pragma once

#include "Core.hpp"
#include "Core_StringView.hpp"
#include "Core_Optional.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	ConsoleCommandParser
		// Desc	:	Class to turn a command-line string into a command name and typed arguments
		//-----------------------------------------------------------------------------------------
		class ConsoleCommandParser final
		{
			public:

				//=================================================================================
				// Public Types
				//=================================================================================
				struct ParseState
				{
					ParseState(StringView anInputString)
						: myInputString(anInputString)
					{

					}

					bool IsAtEnd()
					{
						return myEndIndex == myInputString.length();
					}

					char Peek()
					{
						ALBA_ASSERT(!IsAtEnd(), "Attempting to read beyond end of input");
						return myInputString[myEndIndex];
					}

					char Read()
					{
						ALBA_ASSERT(!IsAtEnd(), "Attempting to read beyond end of input");
						const char current = myInputString[myEndIndex];
						++myEndIndex;

						return current;
					}

					void Skip()
					{
						ALBA_ASSERT(!IsAtEnd(), "Attempting to read beyond end of input");
						++myEndIndex;
					}

					StringView GetToken() const
					{
						return myInputString.substr(myStartIndex, myEndIndex - myStartIndex);
					}

					void StartNextToken()
					{
						myStartIndex = myEndIndex;
					}

					StringView	myInputString;

					size_t		myStartIndex	= 0;
					size_t		myEndIndex		= 0;
				};

				//=================================================================================
				// Public Methods
				//=================================================================================
				static std::tuple<bool, ParseState> ParseCommandName(ParseState anInputState);
				static std::tuple<bool, ParseState> SkipWhitespace(ParseState anInputState);
		};
	}
}