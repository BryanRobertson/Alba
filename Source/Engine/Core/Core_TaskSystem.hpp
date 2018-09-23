#pragma once

#include "Core.hpp"
#include "Core_Thread.hpp"
#include "Core_Task.hpp"

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
				// Private Data
				//=================================================================================
				
		};
	}
}