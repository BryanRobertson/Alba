#include "Graphics_Precompile.hpp"
#include "Graphics_ImGuiModule.hpp"
#include "Graphics_Module.hpp"
#include "Graphics_Debug.hpp"

#ifdef ALBA_PLATFORM_WINDOWS
	#include <Windows.h>

	#include <imgui.h>
	#include <imgui.cpp>
	#include <imgui_draw.cpp>
	
	#include <examples/imgui_impl_win32.h>
	#include <examples/imgui_impl_win32.cpp>

#endif

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool ImGuiModule::OnLoad(Core::AnyDictionary /*someLoadParams*/)
		{
			GraphicsModule& graphicsModule = GraphicsModule::Get();
			if ( !graphicsModule.IsLoaded() )
			{
				ALBA_LOG_ERROR(Graphics, "Failed to load ImGui module - graphics module not loaded!");
				return false;
			}

			// Windows implementation
			#ifdef ALBA_PLATFORM_WINDOWS
			{
				const GraphicsService& graphicsService = graphicsModule.GetGraphicsService();
				if (!graphicsService.GetPlatformData().Has<HWND>())
				{
					ALBA_LOG_ERROR(Graphics, "Failed to load ImGui module - failed to get window handle!");
					return false;
				}

				const HWND windowHandle = graphicsService.GetPlatformData().Get<HWND>();
				if (!ImGui_ImplWin32_Init(windowHandle))
				{
					ALBA_LOG_ERROR(Graphics, "Failed to load ImGui module - failed to initialise ImGui!");
					return false;
				}
			}
			#endif

			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ImGuiModule::OnUnload()
		{
			ImGui_ImplWin32_Shutdown();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ImGuiModule::BeginFrame()
		{
			ImGui_ImplWin32_NewFrame();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ImGuiModule::EndFrame()
		{

		}
	}
}