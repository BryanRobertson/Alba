#pragma once

#include "Core_Module.hpp"
#include "Core_Array.hpp"
#include "Core_StringHash.hpp"
#include "Graphics_API.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	ConsoleModule
		// Desc	:	Module that implements the logic side of a debug command console
		//-----------------------------------------------------------------------------------------
		class ALBA_GRAPHICS_API ConsoleModule final : public Core::Module<ConsoleModule>
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static constexpr const char* GetModuleName() { return "Alba.Graphics.Console"; }

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

				void		Show();
				void		Hide();
				void		ToggleVisibility();

				void		Render();

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				bool		myShowConsole;
		};
	}
}