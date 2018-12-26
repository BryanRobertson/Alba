#include "Core_Precompile.hpp"
#include "Core.hpp"
#include "Core_TaskWorker.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		int	TaskWorker::Join()
		{
			myQuit.store(true, std::memory_order_relaxed);

			if (myThread.joinable())
			{
				myThread.join();
			}

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TaskWorker::Run()
		{
			myThread = Thread([this]()
			{
				while (!myQuit.load(std::memory_order_acquire))
				{
					Yield();
				}
			});
		}
	}
}