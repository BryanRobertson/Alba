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
#include "Core_Profile.hpp"

#include "Graphics.hpp"

#include "Framework.hpp"
#include "Framework_GameApplication.hpp"

#include "Gravity_Module.hpp"

ALBA_IMPLEMENT_LOG_CATEGORY(GravityDemo);

namespace GravityDemo
{
	void InitApplicationParams(Alba::Framework::ApplicationInitParams& anInitParamsOut);
}

#if ALBA_PLATFORM_WINDOWS

	//-------------------------------------------------------------------------------------------------
	// WinMain
	//-------------------------------------------------------------------------------------------------
	int CALLBACK WinMain(_In_ HINSTANCE /*hInstance*/, _In_ HINSTANCE /*hPrevInstance*/, _In_ LPSTR /*lpCmdLine*/, _In_ int /*nCmdShow*/)
	{
		using namespace Alba::BasicTypes;
		using namespace Alba::StringHashLiterals;

		using Alba::Core::UniquePtr;
		using Alba::Core::StringHash32;
		using Alba::Framework::GameApplication;

		//-----------------------------------------------------------------------------------------
		// Initialise framework
		//-----------------------------------------------------------------------------------------
		Alba::Framework::FrameworkInitParams frameworkInitParams;
		frameworkInitParams.myCommandLineParameters = Alba::Core::CommandLineParameters::CreateWindows();

		//-----------------------------------------------------------------------------------------
		// Init
		//-----------------------------------------------------------------------------------------
		if (const uint32 result = Alba::Framework::Init(frameworkInitParams) != 0)
		{
			return result;
		}

		//-----------------------------------------------------------------------------------------
		// Register modules
		//-----------------------------------------------------------------------------------------
		{
			//-------------------------------------------------------------------------------------
			// Register
			//-------------------------------------------------------------------------------------
			Alba::Core::RegisterModules();
			Alba::Graphics::RegisterModules();
			Alba::Framework::RegisterModules();
			Alba::Gravity::RegisterModules();
		}

		//-----------------------------------------------------------------------------------------
		// Init application parameters
		//-----------------------------------------------------------------------------------------
		Alba::Framework::ApplicationInitParams initParams;
		GravityDemo::InitApplicationParams(initParams);

		//-----------------------------------------------------------------------------------------
		// Run
		//-----------------------------------------------------------------------------------------
		UniquePtr<Alba::Framework::GameApplication> application = Alba::Framework::GameApplication::Create();
		{
			const uint32 initResult = application->Init(std::move(initParams));
			if (initResult != 0)
			{
				return initResult;
			}
		}

		//-------------------------------------------------------------------------------------
		// Load main module
		//-------------------------------------------------------------------------------------
		Alba::Core::ModuleRepository& moduleRepository = Alba::Core::ModuleRepository::Get();
		moduleRepository.LoadModule("Alba.Gravity"_nocasehash32);

		const uint32 returnCode = application->Run();

		//-----------------------------------------------------------------------------------------
		// Shutdown
		//-----------------------------------------------------------------------------------------
		Alba::Framework::Shutdown();

		return returnCode;
	}

#endif

namespace GravityDemo
{
	//---------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------
	void InitApplicationParams(Alba::Framework::ApplicationInitParams& anInitParamsOut)
	{
		using namespace Alba::StringHashLiterals;

		const Alba::Core::CommandLineParameters& commandLine = Alba::Core::CommandLineModule::Get().GetParams();	

		// Init window params
		int windowPosX = 100;
		int windowPosY = 100;
		int windowWidth = 800;
		int windowHeight = 600;

		commandLine.TryGetParamValue("windowPosX"_nocasehash32, windowPosX);
		commandLine.TryGetParamValue("windowPosY"_nocasehash32, windowPosY);
		commandLine.TryGetParamValue("windowWidth"_nocasehash32, windowWidth);
		commandLine.TryGetParamValue("windowHeight"_nocasehash32, windowHeight);

		Alba::Core::WindowInitParams& windowParams = anInitParamsOut.myWindowInitParams;

		windowParams.myIsHidden = false;
		windowParams.myPositionX = windowPosX;
		windowParams.myPositionY = windowPosY;
		windowParams.mySizeX = windowWidth;
		windowParams.mySizeY = windowHeight;
	}
}