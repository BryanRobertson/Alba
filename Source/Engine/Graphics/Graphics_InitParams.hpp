#pragma once

#include "Core.hpp"
#include "Core_AnyDictionary.hpp"
#include "Graphics_API.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------------
		// Name	:	InitParams
		// Desc:	Initialisation parameters for the framework
		//-----------------------------------------------------------------------------------------------
		struct ALBA_GRAPHICS_API InitParams
		{
			// Platform specific data
			Core::AnyDictionary		myPlatformData;

			// Window params
			int						myWindowWidth	= 800;
			int						myWindowHeight	= 600;
			bool					myIsFullScreen	= false;
			
			// Misc params
			bool					myEnableImGui  = true;
		};
	}
}