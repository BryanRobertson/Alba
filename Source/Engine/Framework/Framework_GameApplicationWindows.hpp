#pragma once

#include "Core.hpp"
#include "Core_Window.hpp"
#include "Core_UniquePtr.hpp"
#include "Core_PlatformHeader.hpp"
#include "Framework_API.hpp"

#if defined(ALBA_PLATFORM_WINDOWS)

#undef CreateWindow // Damn it, Windows.h
#undef min
#undef max

namespace Alba
{
	namespace Framework
	{
		struct ApplicationInitParams;

		//-----------------------------------------------------------------------------------------
		// Name	:	GameApplicationWindows
		// Desc	:	Game application class for the windows platform
		//-----------------------------------------------------------------------------------------
		class GameApplicationWindows final
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static Core::UniquePtr<GameApplicationWindows> Create();

				//=================================================================================
				// Public Constructors
				//=================================================================================
				GameApplicationWindows();
				~GameApplicationWindows();

				//=================================================================================
				// Public Methods
				//=================================================================================
				uint32		Init(ApplicationInitParams anInitParams);
				uint32		Run();
				uint32		Shutdown();

				void		Quit();

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				uint32		CreateWindow(const Core::WindowInitParams& aWindowInitParams);
				LRESULT		WindowHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

				//=================================================================================
				// Private Data
				//=================================================================================
				Core::UniquePtr<Core::Window> myWindow;
				ApplicationInitParams		  myInitParams;
				bool						  myQuit;
		};
	}
}

#endif