#include "Core_Precompile.hpp"
#include "Core_TaskSystem.hpp"
#include "Core_TaskDebug.hpp"
#include "Core_Logging.hpp"
#include "Core_Memory.hpp"

namespace Alba
{
	namespace Core
	{
		TaskSystem theTaskSystem;

		namespace Detail
		{
			thread_local TaskThreadId theLocalThreadId;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ TaskSystem& TaskSystem::GetMutable()
		{
			return theTaskSystem;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ void TaskSystem::Initialise(uint aThreadCount)
		{
			// Set main thread id
			Detail::theLocalThreadId = theMainThreadId;

			theTaskSystem.InitialiseInternal(aThreadCount);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ void TaskSystem::Shutdown()
		{
			theTaskSystem.ShutdownInternal();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ void TaskSystem::QueueTask(Task& /*aTask*/)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ TaskThreadId	TaskSystem::GetCurrentThreadId()
		{
			return Detail::theLocalThreadId;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TaskSystem::TaskSystem()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TaskSystem::~TaskSystem()
		{
			ALBA_ASSERT(myThreadCount == 0, "Quitting, but task system is still running!");

			if (myThreadCount > 0)
			{
				ShutdownInternal();
			}			
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TaskSystem::InitialiseInternal(uint aThreadCount)
		{
			ALBA_LOG_INFO(Task, "--------------------------------------------------");
			ALBA_LOG_INFO(Task, "Initialising Task System with %u worker threads...");
			ALBA_LOG_INFO(Task, "--------------------------------------------------");

			ALBA_ASSERT(myTaskPools == nullptr);
			ALBA_ASSERT(myTaskWorkers == nullptr);

			myThreadCount = aThreadCount;

			// Create a task pool for all threads (plus an extra one for the main thread)
			myTaskPools = new TaskPool[aThreadCount + 1];
			for (uint index = 0; index < aThreadCount + 1; ++index)
			{
				TaskThreadId id{ static_cast<uint16>(index) };
				myTaskPools[index].Init(id);
			}

			// Create a worker for all threads
			if (aThreadCount > 0)
			{
				myTaskWorkers = new TaskWorker[aThreadCount];
				for (uint index = 0; index < aThreadCount; ++index)
				{
					TaskThreadId id{ static_cast<uint16>(index + 1) };

					myTaskWorkers[index].Init(id);
					myTaskWorkers[index].Run();
				}
			}			
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TaskSystem::ShutdownInternal()
		{
			ALBA_LOG_INFO(Task, "--------------------------------------------------");
			ALBA_LOG_INFO(Task, "Shutting down task system...");
			ALBA_LOG_INFO(Task, "--------------------------------------------------");

			// Join all threads
			for (uint index=0; index < myThreadCount; ++index)
			{
				myTaskWorkers[index].Join();
			}

			delete[] myTaskPools;
			myTaskPools = nullptr;

			if (myThreadCount > 0)
			{
				delete[] myTaskWorkers;
				myTaskWorkers = nullptr;
			}			

			myThreadCount = 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TaskSystem::BeginFrame()
		{
			
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TaskSystem::EndFrame()
		{
			
		}
	}
}