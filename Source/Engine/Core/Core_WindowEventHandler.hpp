#pragma once

#include "Core.hpp"
#include "Core_PlatformHeader.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	WindowEventHandler
		// Desc	:	Allows applications to handle events in the window event handler function
		//-----------------------------------------------------------------------------------------
		struct WindowEventHandler
		{
			//=====================================================================================
			// Public Types
			//=====================================================================================
			typedef LRESULT(*HandlerFunc)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

			//=====================================================================================
			// Public Data Members
			//=====================================================================================
			HandlerFunc myHandlerFunc = nullptr;
		};
	}
}