#include "Core_Precompile.hpp"
#include "Core.hpp"
#include "Core_TaskWorker.hpp"
#include "Core_Time.hpp"
#include "Core_ChronoLiterals.hpp"
#include "Core_FixedString.hpp"
#include "Core_Profile.hpp"
#include "Core_Logging.hpp"
#include "Core_TaskDebug.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TaskWorker::TaskWorker()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TaskWorker::Init(TaskThreadId aTaskThreadId)
		{
			myThreadId = aTaskThreadId;
		}

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
			using namespace Alba::ChronoLiterals;

			myThread = Thread([this]()
			{
				ALBA_ASSERT(myThreadId.IsValid());

				const Core::FixedString<256> threadName("TaskThread_%u", static_cast<unsigned int>(myThreadId.GetValue()));
				ALBA_PROFILE_SETCURRENTTHREADNAME(threadName.c_str());

				ALBA_LOG_INFO(Task, "Task Thread %u Startup", myThreadId);

				while (!myQuit.load(std::memory_order_acquire))
				{
					//Yield();
					Sleep(1_milliseconds);
				}

				ALBA_LOG_INFO(Task, "Task Thread %u Shutting Down", myThreadId);
			});
		}
	}
}