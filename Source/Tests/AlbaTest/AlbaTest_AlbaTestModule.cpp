#include "AlbaTest_Precompile.hpp"
#include "AlbaTest_AlbaTestModule.hpp"

#include "AlbaTest_Core_EnumerationSet.hpp"
#include "AlbaTest.hpp"

#include "Core_Logging.hpp"

namespace Alba
{
	namespace Tests
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool AlbaTestModule::OnLoad(Core::AnyDictionary someParameters)
		{
			ALBA_LOG_INFO(AlbaTest, "-----------------------------------------------------");
			ALBA_LOG_INFO(AlbaTest, "Test Core::EnumerationSet");
			ALBA_LOG_INFO(AlbaTest, "-----------------------------------------------------");
			{
				ALBA_TEST(Test_CoreEnumerationSet());
			}
			ALBA_LOG_INFO(AlbaTest, "-----------------------------------------------------");
			ALBA_LOG_INFO(AlbaTest, "Tests Passed");
			ALBA_LOG_INFO(AlbaTest, "-----------------------------------------------------");

			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void AlbaTestModule::OnUnload()
		{

		}
	}
}
