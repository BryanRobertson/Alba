#include "Framework_Precompile.hpp"
#include "Framework.hpp"
#include "Framework_GameApplication.hpp"

#include "Graphics_Module.hpp"

#include "Core.hpp"

#include "Core_Window.hpp"
#include "Core_ModuleRepository.hpp"
#include "Core_CommandLineModule.hpp"
#include "Core_Any.hpp"
#include "Core_StringHash.hpp"
#include "Core_Profile.hpp"
#include "Core_TaskSystem.hpp"

namespace Alba
{
	namespace Framework
	{
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
			#if defined(ALBA_DEBUG_LOGGING_ENABLED)
				Alba::Core::LogManager::CreateInstance();
			#endif

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

			//----------------------------------------------------------------------
			// Initialise the task system
			//----------------------------------------------------------------------
			{
				const int hardwareThreads = std::thread::hardware_concurrency();
				ALBA_LOG_INFO(Framework, "System supports %u hardware threads", hardwareThreads);

				const int threadCount = std::max(1, hardwareThreads - 1);
				Core::TaskSystem::Initialise(threadCount);
			}

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

			//----------------------------------------------------------------------
			// Shut down the task system
			//----------------------------------------------------------------------
			{
				Core::TaskSystem::Shutdown();
			}

			// Shut down module repository
			Alba::Core::ModuleRepository::Destroy();

			// Shut down the logging system
			#if defined(ALBA_DEBUG_LOGGING_ENABLED)
				Alba::Core::LogManager::DestroyInstance();
			#endif

			ALBA_PROFILE_SHUTDOWN();

			return 0;
		}
	}
}
