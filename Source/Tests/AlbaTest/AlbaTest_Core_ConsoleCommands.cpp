#include "AlbaTest_Precompile.hpp"
#include "AlbaTest_Core_ConsoleCommands.hpp"

#include "AlbaTest.hpp"

#include "Core_Console.hpp"

namespace Alba
{
	namespace Tests
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Test_CoreConsoleCommands()
		{
			using namespace Alba::StringViewLiterals;

			//-----------------------------------------------------------------------------------------
			// Create a console that we can use to test our commands
			//-----------------------------------------------------------------------------------------
			Core::Console console{};

			//-----------------------------------------------------------------------------------------
			// Register some commands and test that they work as expected
			//-----------------------------------------------------------------------------------------

			// Simple command with no arguments
			{
				uint64 testValue = 0;

				console.RegisterCommand("simplecommandnoargs", [&testValue]() -> int
				{
					testValue = 123456789012345l;
					return 0;
				});
				
				ALBA_TEST(testValue == 0);
				console.Execute("simplecommandnoargs");
				ALBA_TEST(testValue == 123456789012345l);
			}

			// Command with arguments
			{
				struct test
				{
					int8			testi8		= 0;
					uint32			testu32		= 0;
					float			testFloat	= 0.0f;
					Core::String	testString	= "";
				};				

				test testInstance;

				console.RegisterCommand("commandwithargs", [&testInstance](int8 anArg1, uint32 anArg2, float anArg3, Core::StringView aStringView, const Core::FixedString<64>& aFixedStr, const Core::String& aStr) -> int
				{
					testInstance.testi8 = anArg1;
					testInstance.testu32 = anArg2;
					testInstance.testFloat = anArg3;
					testInstance.testString.assign(aStringView.begin(), aStringView.end());
					testInstance.testString.append(aFixedStr.begin(), aFixedStr.end());
					testInstance.testString.append(aStr.begin(), aStr.end());

					return 0;
				});

				console.Execute("commandwithargs -32 135535 3.14149 this \" is a \" test");

				ALBA_TEST(testInstance.testi8 == -32);
				ALBA_TEST(testInstance.testu32 == 135535);
				ALBA_TEST(Math::IsNearlyEqual(testInstance.testFloat, 3.14149f, Math::Constants<float>::EpsilonE6));
				ALBA_TEST(testInstance.testString == "this is a test");
			}

			return true;
		}
	}
}

