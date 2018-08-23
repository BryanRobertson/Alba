#pragma once

#include "Graphics_API.hpp"
#include "Core_Module.hpp"

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
				static const char* GetModuleName() { return "Alba.Graphics.ImGui"; }
	
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
				ImFont*				myFont = nullptr;
		};
	}
}