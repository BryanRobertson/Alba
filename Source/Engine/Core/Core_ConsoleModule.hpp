#pragma once

#include "Core.hpp"
#include "Core_Module.hpp"
#include "Core_Console.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	ConsoleModule
		// Desc	:	Module that implements the logic side of a debug command console
		//-----------------------------------------------------------------------------------------
		class ConsoleModule final : public Module<ConsoleModule>
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static constexpr Core::StringView GetModuleName() 
				{ 
					return "Alba.Core.Console"; 
				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				bool		OnLoad(Core::AnyDictionary someParameters);
				void		OnUnload();

				inline Console&	GetConsole();

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				UniquePtr<Console>	myConsole;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*inline*/ Console& ConsoleModule::GetConsole()
		{
			return *myConsole;
		}
	}
}
