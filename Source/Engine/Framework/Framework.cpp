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
			using namespace Alba::StringHashLiterals;

			//----------------------------------------------------------------------
			// Initialise logging
			//----------------------------------------------------------------------
			Alba::Core::LogManager::CreateInstance();

			ALBA_LOG_INFO(Framework, "---------------------------------------------------------------");
			ALBA_LOG_INFO(Framework, "Init Framework:");
			ALBA_LOG_INFO(Framework, "---------------------------------------------------------------");

			//----------------------------------------------------------------------
			// Create module repository
			//----------------------------------------------------------------------
			Alba::Core::ModuleRepository::Create();
			
			//----------------------------------------------------------------------
			// Command line module is always registered/loaded by default
			//----------------------------------------------------------------------
			{
				Alba::Core::CommandLineModule::Register();
				Alba::Core::ModuleRepository::Get().LoadModule
				(
					"Alba.Core.CommandLine"_nocasehash32, 
					std::move(aInitParams.myCommandLineParameters)
				);
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
			ALBA_LOG_INFO(Framework, "---------------------------------------------------------------");
			ALBA_LOG_INFO(Framework, "Shutdown Framework:");
			ALBA_LOG_INFO(Framework, "---------------------------------------------------------------");

			// Init module repository
			Alba::Core::ModuleRepository::Destroy();

			// Shut down the logging system
			Alba::Core::LogManager::DestroyInstance();

			ALBA_PROFILE_SHUTDOWN();

			return 0;
		}
	}
}
