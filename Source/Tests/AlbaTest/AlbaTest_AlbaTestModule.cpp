#include "AlbaTest_Precompile.hpp"
#include "AlbaTest_AlbaTestModule.hpp"
#include "Core_Logging.hpp"

namespace Alba
{
	namespace Tests
	{
		ALBA_IMPLEMENT_LOG_CATEGORY(AlbaTest);

		#define ALBA_FAIL_TEST(aCondition, ...)						\
				do 													\
				{ 													\
					ALBA_LOG_ERROR(AlbaTest, __VA_ARGS__); 			\
				} 													\
				while(0)

		#define ALBA_TEST(aCondition)											\
				if ((aCondition))												\
				{																\
					ALBA_LOG_INFO(AlbaTest, "Test passed: %s", #aCondition);	\
				}																\
				else															\
				{																\
					ALBA_FAIL_TEST(aCondition, "Test Failed: %s", #aCondition); \
					ALBA_DEBUG_BREAK();											\
					return false;												\
				}
		
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool AlbaTestModule::OnLoad(Core::AnyDictionary someParameters)
		{
			ALBA_TEST(true);

			ALBA_LOG_INFO(AlbaTest, "Tests Passed");
			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void AlbaTestModule::OnUnload()
		{

		}
	}
}
