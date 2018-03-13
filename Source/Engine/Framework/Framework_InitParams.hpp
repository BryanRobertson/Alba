#pragma once

#include "Framework_API.hpp"
#include "Core_BasicTypes.hpp"
#include "Core_CommandLineParameters.hpp"

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
			typedef Alba::Core::CommandLineParameters CommandLineParameters;

			int		myWindowPosX	= 100;
			int		myWindowPosY	= 100;
			uint	myWindowWidth	= 800;
			uint	myWindowHeight	= 600;
			bool	myIsFullscreen	= false;

			CommandLineParameters myCommandLine;
		};
	}
}