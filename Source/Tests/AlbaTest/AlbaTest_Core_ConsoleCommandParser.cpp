#include "AlbaTest_Precompile.hpp"
#include "AlbaTest_Core_ConsoleCommandParser.hpp"
#include "AlbaTest.hpp"

#include "Core_StringView.hpp"
#include "Core_ConsoleCommandParser.hpp"

namespace Alba
{
	namespace Tests
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Test_CoreConsoleCommandParser()
		{
			using namespace Alba::StringViewLiterals;

			{
				const Core::ConsoleCommandParser::ParseState input{ "  TestCommand.Test_123     asavw44bq3fw3f" };

				Core::ConsoleCommandParser parser;
				auto[isValid, parseState] = parser.ParseCommandName(input);

				ALBA_TEST(isValid);
				ALBA_TEST(Core::StringView token = parseState.GetToken(); token == "TestCommand.Test_123"_sv);
			}

			return true;
		}
	}
}