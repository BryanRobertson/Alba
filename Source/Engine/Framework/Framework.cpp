#include "Framework_Precompile.hpp"
#include "Framework.hpp"
#include "Framework_GameApplication.hpp"

#include "Core.hpp"
//#include "Core_Memory_Impl.hpp"

#include "Core_Window.hpp"
#include "Core_ModuleRepository.hpp"
#include "Core_CommandLineModule.hpp"
#include "Core_Any.hpp"
#include "Core_StringHash.hpp"

namespace Alba
{
	namespace Framework
	{
		ALBA_IMPLEMENT_LOG_CATEGORY(FrameworkLog);

		using Core::UniquePtr;
		using Core::Window;

		//-----------------------------------------------------------------------------------------
		// Initialise Log
		//-----------------------------------------------------------------------------------------
		ALBA_FRAMEWORK_API uint32 InitLog()
		{
			// Init log manager
			Alba::Core::LogManager::CreateInstance();
			return 0;
		}

		//-----------------------------------------------------------------------------------------
		// Initialise Framework
		//-----------------------------------------------------------------------------------------
		uint32 Init(FrameworkInitParams& aInitParams)
		{
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

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		// Shutdown Log
		//-----------------------------------------------------------------------------------------
		uint32 ShutdownLog()
		{
			Core::LogManager::DestroyInstance();
			return 0;
		}
	}
}
