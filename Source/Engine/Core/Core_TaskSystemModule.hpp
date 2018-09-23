#pragma once

#include "Core.hpp"
#include "Core_ThreadPool.hpp"
#include "Core_Module.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	TaskSystemModule
		// Desc	:	Module that implements and provides access to a multithreaded task pool
		//-----------------------------------------------------------------------------------------
		class TaskSystemModule : public Module<TaskSystemModule>
		{
			public:

				//=================================================================================
				// Public Methods
				//=================================================================================
				bool		OnLoad(Core::AnyDictionary someParameters);
				void		OnUnload();

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				ThreadPool	myThreadPool;
		};
	}
}