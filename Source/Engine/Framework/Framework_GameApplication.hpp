#pragma once

#include "Framework_API.hpp"
#include "Core_Config.hpp"
#include "Core_String.hpp"
#include "Core_FixedString.hpp"

namespace Alba
{
	namespace Framework
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	ApplicationInitParams
		//-----------------------------------------------------------------------------------------
		struct ApplicationInitParams
		{
			uint16		 myWindowWidth  = 800;
			uint16		 myWindowHeight = 600;
			int16		 myWindowPosX   = 100;
			int16		 myWindowPosY   = 100;

			Core::String myWindowTitle = "Alba";
		};

		//-----------------------------------------------------------------------------------------
		// GameApplication
		//-----------------------------------------------------------------------------------------
		#if defined(ALBA_PLATFORM_WINDOWS)
			class GameApplicationWindows;
			typedef GameApplicationWindows GameApplication;
		#else
			#error "Alba GameApplication class not defined for this platform!"
		#endif
	}
}

#if defined(ALBA_PLATFORM_WINDOWS)
	#include "Framework_GameApplicationWindows.hpp"
#endif