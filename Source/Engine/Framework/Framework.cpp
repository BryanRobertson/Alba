#include "Framework_Precompile.hpp"
#include "Framework.hpp"
#include "Framework_GameApplication.hpp"

#include "Graphics_Module.hpp"

#include "Core.hpp"
//#include "Core_Memory_Impl.hpp"

#include "Core_Window.hpp"
#include "Core_ModuleRepository.hpp"
#include "Core_CommandLineModule.hpp"
#include "Core_Any.hpp"
#include "Core_StringHash.hpp"
#include "Core_Profile.hpp"

namespace Alba
{
	namespace Framework
	{
		ALBA_IMPLEMENT_LOG_CATEGORY(Framework);

		using Core::UniquePtr;
		using Core::Window;

		//-----------------------------------------------------------------------------------------
		// Initialise Framework
		//-----------------------------------------------------------------------------------------
		uint32 Init(FrameworkInitParams& aInitParams)
		{
			//----------------------------------------------------------------------
			// Initialise logging
			//----------------------------------------------------------------------
			Alba::Core::LogManager::CreateInstance();

			ALBA_LOG_INFO(Framework, "---------------------------------------------------------------");
			ALBA_LOG_INFO(Framework, "Init Framework: CommandLine = %s", aInitParams.myCommandLineString.c_str());
			ALBA_LOG_INFO(Framework, "---------------------------------------------------------------");

			//----------------------------------------------------------------------
			// Create module repository
			//----------------------------------------------------------------------
			Alba::Core::ModuleRepository::Create();

			//----------------------------------------------------------------------
			// Command line module is the always loaded by default
			//----------------------------------------------------------------------
			{
				Core::AnyDictionary params;
				params.Set<Core::String>(aInitParams.myCommandLineString);

				Alba::Core::ModuleRepository::Get().LoadModule("Alba.Core.CommandLine", params);
			}

			// If we fail to initialise log that too
			//ALBA_LOG_ERROR(Framework, "Error initialising Framework: %u", result);

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		// Register Modules Framework
		//-----------------------------------------------------------------------------------------
		uint32 RegisterModules()
		{
			return 0;
		}

		//-----------------------------------------------------------------------------------------
		// Shutdown Framework
		//-----------------------------------------------------------------------------------------
		uint32 Shutdown()
		{
			// Init module repository
			Alba::Core::ModuleRepository::Destroy();

			// Shut down the logging system
			Alba::Core::LogManager::DestroyInstance();

			ALBA_PROFILE_SHUTDOWN();

			return 0;
		}
	}
}
