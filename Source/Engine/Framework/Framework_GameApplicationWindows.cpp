#include "Framework_Precompile.hpp"
#include "Framework_GameApplication.hpp"
#include "Core_Memory.hpp"
#include "Core_Pair.hpp"
#include "Core_Window.hpp"
#include "Core_WindowEventHandler.hpp"

#ifdef CreateWindow // God damn it Windows.h
	#undef CreateWindow
#endif

#ifdef ALBA_PLATFORM_WINDOWS

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