#include "AlbaTest_Precompile.hpp"
#include "AlbaTest_Core_ConsoleCommandParser.hpp"
#include "AlbaTest.hpp"

#include "Core_StringView.hpp"
#include "Core_ConsoleCommandParser.hpp"

#include "Math.hpp"

namespace Alba
{
	namespace Tests
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Test_CoreConsoleCommandParser()
		{
			using namespace Alba::StringViewLiterals;
			using Core::ConsoleCommandParser;
			
			typedef Core::ConsoleCommandParser::ParseState ParseState;

			//-------------------------------------------------------------------------------------
			// Test parsing command name
			//-------------------------------------------------------------------------------------
			{
				const ParseState input{ "  TestCommand.Test_123     asavw44bq3fw3f" };

				Core::ConsoleCommandParser parser;
				auto[isValid, parseState] = parser.ParseCommandName(input);

				ALBA_TEST(isValid);
				ALBA_TEST(Core::StringView token = parseState.GetToken(); token == "TestCommand.Test_123"_sv);
			}

			//-------------------------------------------------------------------------------------
			// Test float parsing
			//-------------------------------------------------------------------------------------
			{
				ALBA_LOG_INFO(AlbaTest, "Test Float parsing");

				{
					float value = 0.0f;
					auto [success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ "1" }, value);

					ALBA_TEST(success && value == 1.0f);
				}

				{
					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ "-1" }, value);

					ALBA_TEST(success && value == -1.0f);
				}

				{
					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ "1.0" }, value);

					ALBA_TEST(success && value == 1.0f);
				}

				{
					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ "-1.0" }, value);

					ALBA_TEST(success && value == -1.0f);
				}

				{
					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ "1." }, value);

					ALBA_TEST(success && value == 1.0f);
				}

				{
					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ "-1." }, value);

					ALBA_TEST(success && value == -1.0f);
				}

				{
					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ "0.5" }, value);

					ALBA_TEST(success && value == 0.5f);
				}

				{
					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ "-0.5" }, value);

					ALBA_TEST(success && value == -0.5f);
				}

				{
					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ ".5" }, value);

					ALBA_TEST(success && value == 0.5f);
				}

				{
					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ "-.5" }, value);

					ALBA_TEST(success && value == -0.5f);
				}

				{
					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ "+1234.5321" }, value);

					ALBA_TEST(success && value == 1234.5321f);
				}

				{
					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ "-1234.5321" }, value);

					ALBA_TEST(success && value == -1234.5321f);
				}

				{
					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ "1234E+34" }, value);

					ALBA_TEST(success && Math::IsNearlyEqual(value, 1234E+34f));
				}

				{
					const Core::StringView strValue{ "1234E-34" };

					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ strValue }, value);

					float value2 = 0.0f;
					sscanf_s(strValue.data(), "%f", &value2);

					ALBA_TEST(success && Math::IsNearlyEqual(value, value2));
				}

				{
					const Core::StringView strValue{ "3.1413E+34" };

					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ strValue }, value);

					float value2 = 0.0f;
					sscanf_s(strValue.data(), "%f", &value2);

					ALBA_TEST(success && Math::IsNearlyEqual(value, value2));
				}

				{
					const Core::StringView strValue{ "3.1413E-34" };

					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ strValue }, value);

					float value2 = 0.0f;
					sscanf_s(strValue.data(), "%f", &value2);

					ALBA_TEST(success && Math::IsNearlyEqual(value, value2));
				}

				{
					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ "elephant+34" }, value);

					ALBA_TEST(!success);
				}

				{
					float value = 0.0f;
					auto[success, parseState] = ConsoleCommandParser::ParseFloat(ParseState{ "1.2345ababa" }, value);

					ALBA_TEST(!success);
				}
			}

			//-------------------------------------------------------------------------------------
			// Test integer parsing
			//-------------------------------------------------------------------------------------
			{
				ALBA_LOG_INFO(AlbaTest, "Test Integer parsing");

				{
					uint8 value = 0;
					auto[success, parseState] = ConsoleCommandParser::ParseInt(ParseState{ "145" }, value);

					ALBA_TEST(success && value == 145);
				}

				{
					int8 value = 0;
					auto[success, parseState] = ConsoleCommandParser::ParseInt(ParseState{ "-15" }, value);

					ALBA_TEST(success && value == -15);
				}

				{
					uint16 value = 0;
					auto[success, parseState] = ConsoleCommandParser::ParseInt(ParseState{ "65512" }, value);

					ALBA_TEST(success && value == 65512);
				}

				{
					int16 value = 0;
					auto[success, parseState] = ConsoleCommandParser::ParseInt(ParseState{ "-3456" }, value);

					ALBA_TEST(success && value == -3456);
				}

				{
					uint32 value = 0;
					auto[success, parseState] = ConsoleCommandParser::ParseInt(ParseState{ "11345" }, value);

					ALBA_TEST(success && value == 11345);
				}

				{
					int32 value = 0;
					auto[success, parseState] = ConsoleCommandParser::ParseInt(ParseState{ "-13456" }, value);

					ALBA_TEST(success && value == -13456);
				}

				{
					uint64 value = 0;
					auto[success, parseState] = ConsoleCommandParser::ParseInt(ParseState{ "56754" }, value);

					ALBA_TEST(success && value == 56754);
				}

				{
					int64 value = 0;
					auto[success, parseState] = ConsoleCommandParser::ParseInt(ParseState{ "-56754" }, value);

					ALBA_TEST(success && value == -56754);
				}

				{
					int64 value = 0;
					auto[success, parseState] = ConsoleCommandParser::ParseInt(ParseState{ "-56754a" }, value);

					ALBA_TEST(!success);
				}

				{
					int64 value = 0;
					auto[success, parseState] = ConsoleCommandParser::ParseInt(ParseState{ "elephant" }, value);

					ALBA_TEST(!success);
				}
			}

			
			return true;
		}
	}
}