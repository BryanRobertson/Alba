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
		TaskId CreateTaskId(TaskThreadId aThreadId)
		{
			static Atomic<uint32> ourTaskIdCounter = 0;

			const uint32 counter = ourTaskIdCounter.fetch_add(1, std::memory_order_acq_rel);

			const uint8 threadId = static_cast<uint8>(aThreadId.GetValue());
			const uint32 id = (threadId << 24) | (counter & 0xFFFFFF);

			return TaskId(id);
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
		TaskThreadId TaskSystem::GetMainThreadId()
		{
			return theMainThreadId;
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
			ALBA_LOG_INFO(Task, "Initialising Task System with %u worker threads...", aThreadCount);
			ALBA_LOG_INFO(Task, "--------------------------------------------------");

			ALBA_ASSERT(myTaskPools == nullptr);
			ALBA_ASSERT(myTaskWorkers == nullptr);

			myThreadCount = aThreadCount;

			constexpr uint32 ourTasksPerThread = 512;

			// Create a task pool for all threads (plus an extra one for the main thread)
			myTaskPools = new TaskPool[aThreadCount + 1];
			for (uint index = 0; index < aThreadCount + 1; ++index)
			{
				myTaskPools[index].Init(ourTasksPerThread);
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
		TaskPool& TaskSystem::GetCurrentThreadTaskPool()
		{
			return GetTaskPoolMutable(GetCurrentThreadId());
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TaskThreadId TaskSystem::GetOriginatingThreadId(TaskId aTaskId)
		{
			const uint16 threadId = aTaskId.GetValue() >> 24;
			return TaskThreadId(threadId);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TaskPool& TaskSystem::GetTaskPoolMutable(TaskId aTaskId)
		{
			ALBA_ASSERT(aTaskId.IsValid());;
			return GetTaskPoolMutable(GetOriginatingThreadId(aTaskId));
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TaskPool& TaskSystem::GetTaskPoolMutable(TaskThreadId aTaskThreadId)
		{
			const uint16 index = aTaskThreadId.GetValue();
			ALBA_ASSERT(index < TaskSystem::GetMutable().myThreadCount, "Thread index %u out of range", static_cast<uint>(index));

			return TaskSystem::GetMutable().myTaskPools[aTaskThreadId.GetValue()];
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Task* TaskSystem::AllocateTask()
		{
			const TaskThreadId threadId = GetCurrentThreadId();
			ALBA_ASSERT(threadId.IsValid());

			Task* task = GetTaskPoolMutable(threadId).AllocateTask();
			task->myTaskId = CreateTaskId(threadId);

			return task;
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