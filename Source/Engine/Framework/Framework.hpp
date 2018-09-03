#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "Core.hpp"
#include "Core_String.hpp"

#include "Framework_API.hpp"
#include "Framework_Debug.hpp"

namespace Alba
{
	namespace Core { class Window;  }

	namespace Framework
	{
		//-----------------------------------------------------------------------------------------------
		// Name	:	InitParams
		// Desc:	Initialisation parameters for the framework
		//-----------------------------------------------------------------------------------------------
		struct ALBA_FRAMEWORK_API FrameworkInitParams
		{
			Core::CommandLineParameters myCommandLineParameters;
		};

		//-----------------------------------------------------------------------------------------
		// Init Framework
		//-----------------------------------------------------------------------------------------
		ALBA_FRAMEWORK_API uint32 Init(FrameworkInitParams& aParams);

		//-----------------------------------------------------------------------------------------
		// Register Modules Framework
		//-----------------------------------------------------------------------------------------
		ALBA_FRAMEWORK_API uint32 RegisterModules();

		//-----------------------------------------------------------------------------------------
		// Shutdown Framework
		//-----------------------------------------------------------------------------------------
		ALBA_FRAMEWORK_API uint32 Shutdown();
	}
}