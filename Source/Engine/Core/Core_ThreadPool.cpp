#include "Core_Precompile.hpp"
#include "Core_ThreadPool.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ UniquePtr<ThreadPool> ThreadPool::ourInstance = nullptr;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ void ThreadPool::CreateInstance(uint aThreadCount)
		{
			ourInstance.reset(ALBA_NEW(Alba::Core::AllocationType::Framework, "ThreadPool") ThreadPool(aThreadCount));
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ void	ThreadPool::DestroyInstance()
		{
			ourInstance.reset();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ ThreadPool& ThreadPool::GetInstance()
		{
			return *ourInstance;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		ThreadPool::ThreadPool(uint aThreadCount)
			: myIsRunning(false)
		{
			myThreads.reserve(aThreadCount);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		ThreadPool::~ThreadPool()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ThreadPool::Start()
		{
			myIsRunning.store(false);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ThreadPool::Stop()
		{
			myIsRunning.store(false);
		}
	}
}