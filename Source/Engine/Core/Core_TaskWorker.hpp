#pragma once

#include "Core.hpp"
#include "Core_Thread.hpp"
#include "Core_TaskIdTypes.hpp"

#include <thread>

namespace Alba
{
	namespace Core
	{
		class TaskPool;

		//-----------------------------------------------------------------------------------------------
		// Name	:	TaskWorker
		// Desc	:	Worker thread for the task system
		//-----------------------------------------------------------------------------------------------
		class TaskWorker
		{
			public:

				//=======================================================================================
				// Public Constructors
				//=======================================================================================
				template <typename TFunc, class=std::is_invocable<TFunc, int(TaskWorker&)> >
				explicit TaskWorker(TaskThreadId anId, TFunc&& aFunc)
					: myThread(aFunc, *this)
				{

				}

				TaskWorker(TaskWorker& aCopyFrom) = delete;
				TaskWorker(TaskWorker&& aMoveFrom) = default;

				//=======================================================================================
				// Public Methods
				//=======================================================================================
				ALBA_FORCEINLINE TaskThreadId GetId() const;
				int				 Join();

			private:

				//=======================================================================================
				// Private Methods
				//=======================================================================================

				//=======================================================================================
				// Private Data
				//=======================================================================================
				TaskThreadId	myThreadId			= TaskThreadId::InvalidId;
				TaskPool*		myThreadTaskPool	= nullptr;
				std::thread		myThread;
		};

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		TaskThreadId TaskWorker::GetId() const
		{
			return myThreadId;
		}
	}
}