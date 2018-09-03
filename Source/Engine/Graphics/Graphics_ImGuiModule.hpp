#pragma once

#include "Core_Module.hpp"
#include "Core_Array.hpp"
#include "Graphics_API.hpp"
#include "Graphics_ImGui.hpp"

struct ImFont;

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	ImGuiModule
		// Desc	:	Module to wrap the ImGui library
		//-----------------------------------------------------------------------------------------
		class ImGuiModule : public Core::Module<ImGuiModule>
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static constexpr const char* GetModuleName() 
				{ 
					return "Alba.Graphics.ImGui"; 
				}

				static constexpr auto GetDependencies()
				{
					using namespace Alba::StringHashLiterals;
					return Core::Array<Core::NoCaseStringHash32, 1>{ {"Alba.Graphics"_nocasehash32}};
				}
	
				//=================================================================================
				// Public Methods
				//=================================================================================
				bool				OnLoad(Core::AnyDictionary someLoadParams);
				void				OnUnload();

				void				BeginFrame();
				void				EndFrame();

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				#if defined(ALBA_IMGUI_ENABLED)
				ImFont*				myFont = nullptr;
				#endif
		};
	}
}