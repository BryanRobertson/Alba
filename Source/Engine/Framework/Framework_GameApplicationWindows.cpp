#include "Framework_Precompile.hpp"
#include "Core.hpp"

#ifdef ALBA_PLATFORM_WINDOWS

#include "Framework_GameApplication.hpp"
#include "Graphics_ImGuiModule.hpp"
#include "Input_Module.hpp"
#include "Input_Service.hpp"
#include "Core_Memory.hpp"
#include "Core_Pair.hpp"
#include "Core_Window.hpp"
#include "Core_WindowEventHandler.hpp"

#include "Graphics_ImGui.hpp"

#if defined(ALBA_IMGUI_ENABLED)
#	include <examples/imgui_impl_win32.h>
#endif

#ifdef CreateWindow // God damn it Windows.h
	#undef CreateWindow
#endif

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Alba
{
	namespace Framework
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	GameWindowEventHandlerImpl
		// Desc	:	Wraps the Window API message handler
		//-----------------------------------------------------------------------------------------
		struct GameWindowEventHandlerImpl
		{
			//-----------------------------------------------------------------------------------------
			//-----------------------------------------------------------------------------------------
			static LRESULT EventHandler(GameApplication& anApplication, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
			{
				#if defined(ALBA_IMGUI_ENABLED)
				{
					if (Graphics::ImGuiModule::IsLoaded())
					{
						ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

						ImGuiIO& io = ImGui::GetIO();
						
						//-----------------------------------------------------
						// Set input flags based on ImGui input state
						//-----------------------------------------------------
						ALBA_ASSERT(Input::InputModule::IsLoaded());

						Input::InputModule& inputModule		= Input::InputModule::Get();
						Input::InputService& inputService	= inputModule.GetInputServiceMutable();
						auto& inputServiceFlags				= inputService.GetStateFlagsMutable();

						if (io.WantCaptureKeyboard)
						{
							inputServiceFlags.Insert(Alba::Input::UIHasExclusiveKeyboardFocus);
						}
						else
						{
							inputServiceFlags.Remove(Alba::Input::UIHasExclusiveKeyboardFocus);
						}
						
						if (io.WantCaptureMouse)
						{
							inputServiceFlags.Insert(Alba::Input::UIHasExclusiveMouseFocus);
						}
						else
						{
							inputServiceFlags.Remove(Alba::Input::UIHasExclusiveMouseFocus);
						}
					}
				}
				#endif

				switch (uMsg)
				{
					case WM_CLOSE:
					{
						PostQuitMessage(0);
					}
					break;

					case WM_DESTROY:
					case WM_QUIT:
					{
						anApplication.Quit();
					}
					break;
				}

				//---------------------------------------------------------------------------------
				// If the window has an input handler - then call it for input-related messages
				//---------------------------------------------------------------------------------
				if (anApplication.myWindow)
				{
					auto& windowInputHandler = anApplication.myWindow->GetInputHandler();
					if (windowInputHandler.myHandlerFunc)
					{
						const bool isKeyboardMessage = uMsg >= WM_KEYFIRST && uMsg <= WM_KEYLAST;
						const bool isMouseMessage = uMsg >= WM_MOUSEFIRST && uMsg <= WM_MOUSELAST;

						if (isKeyboardMessage || isMouseMessage)
						{
							if (!windowInputHandler.myHandlerFunc(hWnd, uMsg, wParam, lParam))
							{
								return 0;
							}
						}
					}
				}

				return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 GameApplication::CreateWindow(const Core::WindowInitParams& aWindowInitParams)
		{
			//-------------------------------------------------------------------------------------
			// Create window
			//-------------------------------------------------------------------------------------
			myWindow = Core::Window::Create();
			if (!myWindow->Init(aWindowInitParams))
			{
				return 1;
			}

			//-------------------------------------------------------------------------------------
			// Set event handler
			//-------------------------------------------------------------------------------------
			Alba::Core::WindowEventHandler eventHandler;
			eventHandler.myHandlerFunc = [this](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
			{
				GameApplication& app = *this;
				return GameWindowEventHandlerImpl::EventHandler(app, hWnd, uMsg, wParam, lParam);
			};

			myWindow->SetEventHandler(eventHandler);

			return 0;
		}
	}
}

#endif