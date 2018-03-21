#include "GravityDemoExe_Precompile.hpp"
#include "GravityDemoExe.hpp"

#include "Core_CommandLineParameters.hpp"
#include "Core_Logging.hpp"
#include "Core_LogCategory.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_PlatformHeader.hpp"
#include "Core_Window.hpp"
#include "Core_UniquePtr.hpp"
#include "Core_ModuleRepository.hpp"
#include "Core_CommandLineModule.hpp"
#include "Core_Memory_Impl.hpp"

#include "Framework.hpp"
#include "Framework_GameApplication.hpp"

ALBA_IMPLEMENT_LOG_CATEGORY(GravityDemo);

#if ALBA_PLATFORM_WINDOWS

	//-------------------------------------------------------------------------------------------------
	// WinMain
	//-------------------------------------------------------------------------------------------------
	int CALLBACK WinMain(_In_ HINSTANCE /*hInstance*/, _In_ HINSTANCE /*hPrevInstance*/, _In_ LPSTR lpCmdLine, _In_ int /*nCmdShow*/)
	{
		using Alba::Core::UniquePtr;
		using Alba::Core::StringHash32;
		using Alba::Framework::GameApplication;
		
		using namespace Alba::BasicTypes;

		//--------------------------------------------------------------------------
		// Initialise logging
		//--------------------------------------------------------------------------
		Alba::Framework::InitLog();
		ALBA_LOG_INFO(GravityDemo, "Initialise application - commandLine: %s", lpCmdLine);

		//--------------------------------------------------------------------------
		// Initialise framework
		//--------------------------------------------------------------------------
		Alba::Framework::FrameworkInitParams frameworkInitParams;
		frameworkInitParams.myCommandLineString = lpCmdLine;

		//----------------------------------------------------------------------
		// Init
		//----------------------------------------------------------------------
		if (const uint32 result = Alba::Framework::Init(frameworkInitParams) != 0)
		{
			ALBA_LOG_ERROR(GravityDemo, "Error initialising application: %u", result);
			return result;
		}

		//----------------------------------------------------------------------
		// Register modules
		//----------------------------------------------------------------------
		//Alba::Core::ModuleRepository& moduleRepository = Alba::Core::ModuleRepository::Get();

		Alba::Core::RegisterModules();
		Alba::Framework::RegisterModules();

		//----------------------------------------------------------------------
		// Load modules
		//----------------------------------------------------------------------
		{
			
		}

		//--------------------------------------------------------------------------
		// Run
		//--------------------------------------------------------------------------
		Alba::Framework::ApplicationInitParams initParams;
		const Alba::Core::CommandLineParameters& commandLine = Alba::Core::CommandLineModule::Get().GetParams();

		commandLine.TryGetParamValue("windowPosX", initParams.myWindowPosX);
		commandLine.TryGetParamValue("windowPosY", initParams.myWindowPosY);
		commandLine.TryGetParamValue("windowWidth", initParams.myWindowWidth);
		commandLine.TryGetParamValue("windowHeight", initParams.myWindowHeight);

		UniquePtr<Alba::Framework::GameApplication> application = Alba::Framework::GameApplication::Create();
		const uint32 returnCode = application->Run();

		//--------------------------------------------------------------------------
		// Shutdown
		//--------------------------------------------------------------------------
		Alba::Framework::Shutdown();
		Alba::Framework::ShutdownLog();

		return returnCode;
	}

#endif