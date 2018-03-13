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
#include "Framework.hpp"
#include "Framework_InitParams.hpp"

ALBA_IMPLEMENT_LOG_CATEGORY(GravityDemo);

#if ALBA_PLATFORM_WINDOWS

	//-------------------------------------------------------------------------------------------------
	// WinMain
	//-------------------------------------------------------------------------------------------------
	int CALLBACK WinMain(_In_ HINSTANCE /*hInstance*/, _In_ HINSTANCE /*hPrevInstance*/, _In_ LPSTR lpCmdLine, _In_ int /*nCmdShow*/)
	{
		using Alba::Core::UniquePtr;
		using Alba::Core::StringHash32;
		
		using namespace Alba::BasicTypes;

		//--------------------------------------------------------------------------
		// Initialise logging
		//--------------------------------------------------------------------------
		Alba::Framework::InitLog();
		ALBA_LOG_INFO(GravityDemo, "Initialise application - commandLine: %s", lpCmdLine);

		//--------------------------------------------------------------------------
		// Initialise framework
		//--------------------------------------------------------------------------
		Alba::Framework::InitParams initParams;

		initParams.myCommandLine.Init(lpCmdLine);
		initParams.myCommandLine.TryGetParamValue("windowPosX", initParams.myWindowPosX);
		initParams.myCommandLine.TryGetParamValue("windowPosY", initParams.myWindowPosY);
		initParams.myCommandLine.TryGetParamValue("windowWidth", initParams.myWindowWidth);
		initParams.myCommandLine.TryGetParamValue("windowHeight", initParams.myWindowHeight);

		//----------------------------------------------------------------------
		// Init
		//----------------------------------------------------------------------
		if (const uint32 result = Alba::Framework::Init(initParams) != 0)
		{
			ALBA_LOG_ERROR(GravityDemo, "Error initialising application: %u", result);
			return result;
		}

		Alba::Core::ModuleRepository& moduleRepository = Alba::Core::ModuleRepository::Get();
		
		//----------------------------------------------------------------------
		// Load modules
		//----------------------------------------------------------------------
		{
			Alba::Core::AnyDictionary loadParams;
			loadParams.Set<Alba::Framework::InitParams>(initParams);

			if (!moduleRepository.LoadModule(StringHash32("Alba.FrameworkModule"), loadParams))
			{
				return 1;
			}
		}

		//--------------------------------------------------------------------------
		// Update
		//--------------------------------------------------------------------------
		while (Alba::Framework::Update())
		{

		}

		//--------------------------------------------------------------------------
		// Shutdown
		//--------------------------------------------------------------------------
		Alba::Framework::Shutdown();
		Alba::Framework::ShutdownLog();

		return 0;
	}

#endif