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

#include "Gravity_Module.hpp"

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
		ALBA_LOG_INFO(GravityDemo, "Initialise framework - commandLine: %s", lpCmdLine);

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
			ALBA_LOG_ERROR(GravityDemo, "Error initialising Framework: %u", result);
			return result;
		}

		//----------------------------------------------------------------------
		// Register and Load modules
		//----------------------------------------------------------------------
		{
			Alba::Core::RegisterModules();
			Alba::Framework::RegisterModules();
			Alba::Gravity::RegisterModules();
		}

		//--------------------------------------------------------------------------
		// Run
		//--------------------------------------------------------------------------
		const Alba::Core::CommandLineParameters& commandLine = Alba::Core::CommandLineModule::Get().GetParams();

		Alba::Framework::ApplicationInitParams initParams;

		// Init window params
		int windowPosX = 100;
		int windowPosY = 100;
		int windowWidth = 800;
		int windowHeight = 600;

		commandLine.TryGetParamValue("windowPosX", windowPosX);
		commandLine.TryGetParamValue("windowPosY", windowPosY);
		commandLine.TryGetParamValue("windowWidth", windowWidth);
		commandLine.TryGetParamValue("windowHeight", windowHeight);

		Alba::Core::WindowInitParams& windowParams = initParams.myWindowInitParams;
		windowParams.myIsHidden = false;
		windowParams.myPosition = Alba::Math::Vector2i(windowPosX, windowPosY);
		windowParams.mySize = Alba::Math::Vector2i(windowWidth, windowHeight);

		UniquePtr<Alba::Framework::GameApplication> application = Alba::Framework::GameApplication::Create();
		application->Init(std::move(initParams));

		const uint32 returnCode = application->Run();

		//--------------------------------------------------------------------------
		// Shutdown
		//--------------------------------------------------------------------------
		Alba::Framework::Shutdown();
		Alba::Framework::ShutdownLog();

		return returnCode;
	}

#endif