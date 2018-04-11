#pragma once

#include "Framework_API.hpp"
#include "Core_Config.hpp"
#include "Core_String.hpp"
#include "Core_FixedString.hpp"
#include "Core_Window.hpp"

namespace Alba
{
	namespace Framework
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	ApplicationInitParams
		//-----------------------------------------------------------------------------------------
		struct ApplicationInitParams
		{
			Alba::Core::WindowInitParams myWindowInitParams;
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