#pragma once

namespace Alba
{
	namespace Tests
	{
		using namespace Alba::BasicTypes;

		ALBA_DECLARE_LOG_CATEGORY(AlbaTest);

		#define ALBA_FAIL_TEST(aCondition, ...)									\
				do 																\
				{ 																\
					ALBA_LOG_ERROR(AlbaTest, __VA_ARGS__); 						\
				} 																\
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
		extern void RegisterModules();
	}
}