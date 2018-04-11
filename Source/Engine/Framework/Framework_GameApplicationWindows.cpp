#include "Framework_Precompile.hpp"
#include "Framework_GameApplication.hpp"
#include "Core_Memory.hpp"
#include "Core_Pair.hpp"
#include "Core_Window.hpp"
#include "Core_WindowEventHandler.hpp"

namespace Alba
{
	namespace Framework
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ Core::UniquePtr<GameApplicationWindows> GameApplicationWindows::Create()
		{
			return Core::UniquePtr<GameApplicationWindows>
			(
				ALBA_NEW(Core::AllocationType::Framework, "GameApplicationWindows") GameApplicationWindows()
			);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		GameApplicationWindows::GameApplicationWindows()
			: myQuit(false)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		GameApplicationWindows::~GameApplicationWindows()
		{
			if (myWindow)
			{
				Shutdown();
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 GameApplicationWindows::Init(ApplicationInitParams anInitParams)
		{
			myInitParams = std::move(anInitParams);
			CreateWindow(myInitParams.myWindowInitParams);

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 GameApplicationWindows::CreateWindow(const Core::WindowInitParams& aWindowInitParams)
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
			eventHandler.Bind(this, &GameApplicationWindows::WindowHandler);

			myWindow->SetEventHandler(eventHandler);

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		LRESULT	GameApplicationWindows::WindowHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
					myQuit = true;
				}
				break;
			}

			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 GameApplicationWindows::Run()
		{
			//-------------------------------------------------------------------------------------
			// Update
			//-------------------------------------------------------------------------------------
			myQuit = false;
			while (!myQuit)
			{
				myQuit = !myWindow->Update();
			}

			//-------------------------------------------------------------------------------------
			// Shutdown
			//-------------------------------------------------------------------------------------
			Shutdown();

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 GameApplicationWindows::Shutdown()
		{
			myWindow.reset();

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GameApplicationWindows::Quit()
		{
			myQuit = true;
		}
	}
}