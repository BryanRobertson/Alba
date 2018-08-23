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

			// Init ImGui
			IMGUI_CHECKVERSION();

			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();

			// Windows implementation
			#ifdef ALBA_PLATFORM_WINDOWS
			{
				GraphicsService& graphicsService = graphicsModule.GetGraphicsServiceMutable();
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

				RenderBackEnd& renderBackEnd = graphicsService.GetBackEnd();
				if (!renderBackEnd.ImGuiInit())
				{
					ALBA_LOG_ERROR(Graphics, "Failed to load ImGui module - failed to initialise render backend!");
					return false;
				}
			}
			#endif

			// Load font
			myFont = io.Fonts->AddFontFromFileTTF("../Data/fonts/DroidSans.ttf", 16.0f);
			if (!myFont)
			{
				if (!io.Fonts->AddFontDefault())
				{
					ALBA_LOG_ERROR(Graphics, "Failed to load ImGui module - couldn't load default font!");
					return false;
				}
			}
			/*
			else
			{
				uint8_t* data = nullptr;
				int32_t width = 0;
				int32_t height = 0;

				io.Fonts->GetTexDataAsRGBA32(&data, &width, &height);
			}
			*/

			// Dark style
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