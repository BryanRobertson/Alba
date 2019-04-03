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

				friend class TaskSystem;

				//=======================================================================================
				// Public Constructors
				//=======================================================================================
				explicit TaskWorker();

				TaskWorker(const TaskWorker& aCopyFrom) = delete;
				TaskWorker(TaskWorker&& aMoveFrom) = delete;

				//=======================================================================================
				// Public Methods
				//=======================================================================================
				ALBA_FORCEINLINE TaskThreadId GetId() const;

				void			Init(TaskThreadId aTaskThreadId);

				void			Run();
				int				Join();

				TaskWorker& operator=(const TaskWorker&) = delete;
				TaskWorker& operator=(TaskWorker&&) = delete;

			private:

				//=======================================================================================
				// Private Methods
				//=======================================================================================

				//=======================================================================================
				// Private Data
				//=======================================================================================
				TaskThreadId		myThreadId			= TaskThreadId::InvalidId;
				TaskPool*			myThreadTaskPool	= nullptr;
				std::atomic<bool>	myQuit				= false;

				Thread				myThread;
		};

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		TaskThreadId TaskWorker::GetId() const
		{
			return myThreadId;
		}
	}
}