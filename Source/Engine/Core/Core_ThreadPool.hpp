#pragma once

#include "Core.hpp"
#include "Core_FixedVector.hpp"
#include "Core_UniquePtr.hpp"

//------------------------------------------------------------------------------------------------
// Name	:	Core_ThreadPool.hpp
//------------------------------------------------------------------------------------------------
namespace Alba
{
	namespace Core
	{
		//----------------------------------------------------------------------------------------
		// Name:  ThreadPool
		//----------------------------------------------------------------------------------------
		class ALBA_CORE_API ThreadPool final
		{
			public:

				//================================================================================
				// Public Static Methods
				//================================================================================
				static void			CreateInstance(uint aThreadCount);
				static void			DestroyInstance();
				static ThreadPool&	GetInstance();

				//================================================================================
				// Public Constructors
				//================================================================================
				ThreadPool(uint aThreadCount);
				~ThreadPool();

				//================================================================================
				// Public Methods
				//================================================================================
				void	Start();
				void	Stop();

			private:

				//================================================================================
				// Private Constants
				//================================================================================
				static constexpr int ourThreadCapacity = 32;

				//================================================================================
				// Private Static Data
				//================================================================================
				static UniquePtr<ThreadPool>			ourInstance;

				//================================================================================
				// Private Data
				//================================================================================
				FixedVector<Thread, ourThreadCapacity> myThreads;
				std::atomic<bool>					   myIsRunning;
		};
	}
}