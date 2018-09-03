#include "Graphics_Precompile.hpp"
#include "Graphics_ImGuiModule.hpp"
#include "Graphics_Module.hpp"
#include "Graphics_RenderBackEnd.hpp"
#include "Graphics_Debug.hpp"

#ifdef ALBA_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#ifdef ALBA_PLATFORM_WINDOWS
#	if defined(ALBA_IMGUI_ENABLED)
#		include <examples/imgui_impl_win32.h>
#	endif
#endif

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool ImGuiModule::OnLoad(Core::AnyDictionary /*someLoadParams*/)
		{
			#if defined(ALBA_IMGUI_ENABLED)

				GraphicsModule& graphicsModule = GraphicsModule::Get();
				if ( !graphicsModule.IsLoaded() )
				{
					ALBA_LOG_ERROR(Graphics, "Failed to load ImGui module - graphics module not loaded!");
					return false;
				}

				//-------------------------------------------------------------
				// Init ImGui
				//-------------------------------------------------------------
				IMGUI_CHECKVERSION();

				ImGui::CreateContext();
				ImGuiIO& io = ImGui::GetIO();

				GraphicsService& graphicsService = graphicsModule.GetGraphicsServiceMutable();

				//-------------------------------------------------------------
				// Windows-specific initialisation
				//-------------------------------------------------------------
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
				#else
					#pragma error("Not Implemented");
				#endif

				//-------------------------------------------------------------
				// Load fonts
				//
				// Note: This must be done before initialisation of the render backend
				//		 part of our ImGui init
				//
				//		 Otherwise ImGui won't have our overriden default font when it initialises
				//		 and it'll fall back to the pixellated default font
				//		 (which will then be a pain to override as we'll have to manually PushFont/PopFont
				//		  every frame)
				//-------------------------------------------------------------

				ImFontConfig fontConfig;

				static constexpr const char* const ourDefaultFontPath = "../Data/fonts/Roboto-Medium.ttf"; //"../Data/fonts/DroidSans.ttf";
				static constexpr float ourDefaultFontSize = 14.0f; //16.0f;

				//-------------------------------------------------------------
				// Load default font
				//-------------------------------------------------------------
				{
					ImFont*& defaultFont = myFonts.push_back();

					defaultFont = io.Fonts->AddFontFromFileTTF(ourDefaultFontPath, ourDefaultFontSize, &fontConfig);
					if (!defaultFont)
					{
						defaultFont = io.Fonts->AddFontDefault();
						if (!defaultFont)
						{
							ALBA_LOG_ERROR(Graphics, "Failed to load ImGui module - couldn't load default font!");
							return false;
						}
					}
				}

				//-------------------------------------------------------------
				// Load console font
				//-------------------------------------------------------------
				{
					ImFont*& consoleFont = myFonts.push_back();

					consoleFont = io.Fonts->AddFontFromFileTTF("../Data/fonts/Cousine-Regular.ttf", 14.0f, &fontConfig);
					if (!consoleFont)
					{
						consoleFont = GetDefaultFont();
					}
				}

				//-------------------------------------------------------------
				// Attempt to load a few other fonts
				//-------------------------------------------------------------
				{
					if (ImFont* font = io.Fonts->AddFontFromFileTTF("../Data/fonts/Karla-Regular.ttf", 16.0f, &fontConfig))
					{
						myFonts.push_back(font);
					}

					if (ImFont* font = io.Fonts->AddFontFromFileTTF("../Data/fonts/ProggyClean.ttf", 16.0f, &fontConfig))
					{
						myFonts.push_back(font);
					}

					if (ImFont* font = io.Fonts->AddFontFromFileTTF("../Data/fonts/Roboto-Medium.ttf", 16.0f, &fontConfig))
					{
						myFonts.push_back(font);
					}
				}

				//-------------------------------------------------------------
				// Init render-backend part of ImGui
				//-------------------------------------------------------------
				RenderBackEnd& renderBackEnd = graphicsService.GetBackEnd();
				if (!renderBackEnd.ImGuiInit())
				{
					ALBA_LOG_ERROR(Graphics, "Failed to load ImGui module - failed to initialise render backend!");
					return false;
				}

				//-------------------------------------------------------------
				ImGui::StyleColorsDark();
				return true;

			#else

				ALBA_LOG_ERROR(Graphics, "Failed to load ImGui module - ALBA_IMGUI_ENABLED is not defined!");
				return false;

			#endif			
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ImGuiModule::OnUnload()
		{
#if defined(ALBA_IMGUI_ENABLED)
			GraphicsModule& graphicsModule = GraphicsModule::Get();
			if (graphicsModule.IsLoaded())
			{
				GraphicsService& graphicsService = graphicsModule.GetGraphicsServiceMutable();
				RenderBackEnd& renderBackEnd = graphicsService.GetBackEnd();

				renderBackEnd.ImGuiShutDown();
			}

			ImGui_ImplWin32_Shutdown();
#endif
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ImGuiModule::BeginFrame()
		{
#if defined(ALBA_IMGUI_ENABLED)
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();	

			// 2. Show a simple window that we create ourselves.We use a Begin / End pair to created a named window.
			{
				static bool ourShowDemoWindow = true;
				ImGui::ShowDemoWindow(&ourShowDemoWindow);
			}
#endif
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ImGuiModule::EndFrame()
		{

		}
	}
}