#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "Core.hpp"
#include "Core_LogCategory.hpp"
#include "Core_String.hpp"
#include "Core_CommandLineParameters.hpp"

#include "Framework_API.hpp"

namespace Alba
{
	namespace Core { class Window;  }

	namespace Framework
	{
		ALBA_DECLARE_LOG_CATEGORY(FrameworkLog);

		//-----------------------------------------------------------------------------------------------
		// Name	:	InitParams
		// Desc:	Initialisation parameters for the framework
		//-----------------------------------------------------------------------------------------------
		struct FrameworkInitParams
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