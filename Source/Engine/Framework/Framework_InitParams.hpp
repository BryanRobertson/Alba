#pragma once

#include "Framework_API.hpp"
#include "Core_BasicTypes.hpp"

namespace Alba
{
	namespace Framework
	{
		//-----------------------------------------------------------------------------------------------
		// Name	:	InitParams
		// Desc:	Initialisation parameters for the framework
		//-----------------------------------------------------------------------------------------------
		struct InitParams
		{
			uint		myWindowPosX	= 100;
			uint		myWindowPosY	= 100;
			uint		myWindowWidth	= 800;
			uint		myWindowHeight	= 600;
			bool		myIsFullscreen	= false;
		};
	}
}