#include "AlbaTest_Precompile.hpp"
#include "AlbaTest.hpp"
#include "AlbaTest_AlbaTestModule.hpp"

namespace Alba
{
	namespace Tests
	{
		ALBA_IMPLEMENT_LOG_CATEGORY(AlbaTest);

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void RegisterModules()
		{
			AlbaTestModule::Register();
		}
	}
}