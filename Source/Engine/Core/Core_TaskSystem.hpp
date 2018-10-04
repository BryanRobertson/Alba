#pragma once

#include "Core.hpp"
#include "Core_Thread.hpp"
#include "Core_Vector.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_TaskWrapper.hpp"
#include "Core_Array.hpp"
#include "Core_TaskPool.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	TaskSystem
		// Desc	:	Multithreaded task system, executes a tree of tasks over several threads
		//-----------------------------------------------------------------------------------------
		class TaskSystem final
		{
			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				TaskSystem();
				~TaskSystem();

				//=================================================================================
				// Public Methods
				//=================================================================================
				void	Initialise(uint aThreadCount);
				void	Shutdown();

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================

				//=================================================================================
				// Private Data
				//=================================================================================
				Vector<thread>	mySingleFrameTaskThreads;
				TaskPool<2048>	mySingleFrameTaskPool;

				TaskPool<4096>	myMultiFrameTaskPool;
				Vector<thread>	myMultiFrameTaskThreads;
		};
	}
}