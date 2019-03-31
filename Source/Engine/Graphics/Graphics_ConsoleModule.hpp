#pragma once

#include "Core_Module.hpp"
#include "Core_Array.hpp"
#include "Core_StringHash.hpp"
#include "Core_UniquePtr.hpp"
#include "Core_Console.hpp"
#include "Graphics_API.hpp"
#include "Graphics_Console.hpp"

namespace Alba
{
	namespace Graphics
	{
		class Console;

		//-----------------------------------------------------------------------------------------
		// Name	:	ConsoleModule
		// Desc	:	Module that implements the logic side of a debug command console
		//-----------------------------------------------------------------------------------------
		class ConsoleModule final : public Core::Module<ConsoleModule>
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static constexpr Core::StringView GetModuleName() { return "Alba.Graphics.Console"; }

				// Get dependencies
				static constexpr auto GetDependencies()
				{
					using namespace Alba::StringHashLiterals;

					return Core::Array<Core::NoCaseStringHash32, 2>
					{{
						"Alba.Core.Console"_nocasehash32,
						"Alba.Graphics.ImGui"_nocasehash32
					}};
				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				bool		OnLoad(Core::AnyDictionary someParameters);
				void		OnUnload();

				void		Render();

				//---------------------------------------------------------------------------------
				// Accessors
				//---------------------------------------------------------------------------------
				inline Console&	GetConsole();

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				Core::UniquePtr<Console>		myConsole;
				Core::Console::PrintCallbackId	myPrintCallbackId;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		inline Console& ConsoleModule::GetConsole()
		{
			ALBA_ASSERT(IsLoaded());
			return *myConsole;
		}
	}
}