#include "Graphics_Precompile.hpp"
#include "Graphics_ImGuiModule.hpp"
#include "Graphics_Module.hpp"
#include "Graphics_RenderBackEnd.hpp"
#include "Graphics_Debug.hpp"

#ifdef ALBA_PLATFORM_WINDOWS
	#include <Windows.h>

	#include <imgui.h>
	#include <imgui.cpp>
	#include <imgui_draw.cpp>
	#include <imgui_demo.cpp>
	
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
			myFont = nullptr;

			GraphicsModule& graphicsModule = GraphicsModule::Get();
			if ( !graphicsModule.IsLoaded() )
			{
				ALBA_LOG_ERROR(Graphics, "Failed to load ImGui module - graphics module not loaded!");
				return false;
			}

			//---------------------------------------------
			// Init ImGui
			//---------------------------------------------
			IMGUI_CHECKVERSION();

			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();

			GraphicsService& graphicsService = graphicsModule.GetGraphicsServiceMutable();

			//---------------------------------------------
			// Windows-specific initialisation
			//---------------------------------------------
			#ifdef ALBA_PLATFORM_WINDOWS
			{
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

			//---------------------------------------------
			// Load font
			// Note: This must be done before initialisation of the render backend
			//---------------------------------------------
			myFont = io.Fonts->AddFontFromFileTTF("../Data/fonts/DroidSans.ttf", 16.0f);
			if (!myFont)
			{
				if (!io.Fonts->AddFontDefault())
				{
					ALBA_LOG_ERROR(Graphics, "Failed to load ImGui module - couldn't load default font!");
					return false;
				}
			}

			//---------------------------------------------
			// Init render-backend part of ImGui
			//---------------------------------------------
			RenderBackEnd& renderBackEnd = graphicsService.GetBackEnd();
			if (!renderBackEnd.ImGuiInit())
			{
				ALBA_LOG_ERROR(Graphics, "Failed to load ImGui module - failed to initialise render backend!");
				return false;
			}

			//---------------------------------------------
			ImGui::StyleColorsDark();

			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ImGuiModule::OnUnload()
		{
			GraphicsModule& graphicsModule = GraphicsModule::Get();
			if (graphicsModule.IsLoaded())
			{
				GraphicsService& graphicsService = graphicsModule.GetGraphicsServiceMutable();
				RenderBackEnd& renderBackEnd = graphicsService.GetBackEnd();

				renderBackEnd.ImGuiShutDown();
			}

			ImGui_ImplWin32_Shutdown();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ImGuiModule::BeginFrame()
		{
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			if (myFont && myFont->IsLoaded())
			{
				ImGui::PushFont(myFont);
			}			

			// 2. Show a simple window that we create ourselves.We use a Begin / End pair to created a named window.
			{
				static bool ourShowDemoWindow = true;
				ImGui::ShowDemoWindow(&ourShowDemoWindow);
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ImGuiModule::EndFrame()
		{
			if (myFont && myFont->IsLoaded())
			{
				ImGui::PopFont();
			}
		}
	}
}