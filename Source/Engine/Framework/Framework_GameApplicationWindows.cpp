#include "Framework_Precompile.hpp"
#include "Framework_GameApplication.hpp"
#include "Core_Memory.hpp"
#include "Core_Pair.hpp"

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

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 GameApplicationWindows::Run()
		{
			//-------------------------------------------------------------------------------------
			// Create window
			//-------------------------------------------------------------------------------------
			Core::WindowParams windowParams;
			windowParams.myPosition = Core::Pair<int, int>(myInitParams.myWindowPosX, myInitParams.myWindowPosY);
			windowParams.mySize = Core::Pair<uint16, uint16>(myInitParams.myWindowWidth, myInitParams.myWindowHeight);
			windowParams.myTitle = myInitParams.myWindowTitle.c_str();

			myWindow = Core::Window::Create();
			if ( !myWindow->Init(windowParams) )
			{
				return 1;
			}

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