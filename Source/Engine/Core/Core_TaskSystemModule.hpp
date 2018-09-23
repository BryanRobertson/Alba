#pragma once

#include "Core.hpp"
#include "Core_Module.hpp"
#include "Core_TaskSystem.hpp"

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
				// Public Static Methods
				//=================================================================================
				static constexpr StringView GetModuleName() 
				{ 
					using namespace Alba::StringViewLiterals;
					return "Alba.Core.TaskSystem"sv; 
				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				bool		OnLoad(Core::AnyDictionary someParameters);
				void		OnUnload();

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				TaskSystem	 myTaskSystem;
		};
	}
}