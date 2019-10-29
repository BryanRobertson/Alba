#include "AlbaTest_Precompile.hpp"
#include "AlbaTest_Core_Task.hpp"
#include "AlbaTest.hpp"

#include "Core_TaskSystem.hpp"
#include "Core_TaskWrapper.hpp"

namespace Alba
{
	namespace Tests
	{
		void TaskFunc1(const Core::TaskExecutionContext&)
		{

		}

		void TaskFunc2(const Core::TaskExecutionContext&)
		{

		}

		void TaskFunc3(const Core::TaskExecutionContext&)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Test_CoreTask()
		{
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			{
				const int hardwareThreads = std::thread::hardware_concurrency();
				const int threadCount = std::max(1, hardwareThreads - 1);

				Core::TaskSystem::Initialise(threadCount);
			}
			//-------------------------------------------------------------------------------------
			
			Core::TaskWrapper wrapper;
			auto result = wrapper.CreateDependentTasks
			(
				[](const Core::TaskExecutionContext&)
				{
					
				},
				[](const Core::TaskExecutionContext&)
				{

				},
				[](const Core::TaskExecutionContext&)
				{

				}
			);

			auto result2 = std::get<0>(result).CreateDependentTasks
			(
				&TaskFunc1, &TaskFunc2, &TaskFunc3
			);

			[[maybe_unused]]
			auto& test = std::get<0>(result2);
			
			[[maybe_unused]]
			auto& test1 = std::get<1>(result2);
			
			[[maybe_unused]]
			auto& test2 = std::get<2>(result2);

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			{
				Core::TaskSystem::Shutdown();
			}
			//-------------------------------------------------------------------------------------

			return true;
		}
	}
}

