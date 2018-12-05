#include "AlbaTest_Precompile.hpp"
#include "AlbaTest.hpp"
#include "AlbaTest_AlbaTestModule.hpp"

namespace Alba
{
	namespace Tests
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void RegisterModules()
		{
			AlbaTestModule::Register();
		}
	}
}