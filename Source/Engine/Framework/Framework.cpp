#include "Framework_Precompile.hpp"
#include "Framework.hpp"
#include "Framework_InitParams.hpp"
#include "Framework_Module.hpp"

#include "Core.hpp"

#if defined(ALBA_CORE_LIBRARY_DLL)
#include "Core_Memory_Impl.hpp"
#endif

#include "Core_Window.hpp"
#include "Core_ModuleRepository.hpp"
#include "Core_Any.hpp"

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
		uint32 Init(InitParams& /*aInitParams*/)
		{
			//----------------------------------------------------------------------
			// Init module repository
			//----------------------------------------------------------------------
			Alba::Core::ModuleRepository::Create();

			//----------------------------------------------------------------------
			// Register modules
			//----------------------------------------------------------------------
			FrameworkModule::Register();

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		// Update
		//-----------------------------------------------------------------------------------------
		bool Update()
		{
			return FrameworkModule::Get().GetWindow().Update();
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
