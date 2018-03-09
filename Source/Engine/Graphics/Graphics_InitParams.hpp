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
		struct InitParams
		{
			int				myWindowWidth	= 800;
			int				myWindowHeight	= 600;

			// Platform specific data
			Core::Any		myPlatformData;
		};
	}
}