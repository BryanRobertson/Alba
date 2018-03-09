#pragma once

#include "Core.hpp"

#if defined(ALBA_PLATFORM_WINDOWS)
	#pragma warning( push, 3 )  

		#ifndef WIN32_LEAN_AND_MEAN
			#define WIN32_LEAN_AND_MEAN
		#endif

		#define NOMINMAX
		#include <Windows.h>
		#undef NOMINMAX

	#pragma warning( pop ) 
#endif

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------------
		// Name	:	PlatformData
		//-----------------------------------------------------------------------------------------------
		struct PlatformData
		{
			#if defined(ALBA_PLATFORM_WINDOWS)
				HWND myWindowHandle = NULL;
			#endif
		};
	}
}