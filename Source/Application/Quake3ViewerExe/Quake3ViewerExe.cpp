#include "Quake3ViewerExe_Precompile.hpp"
#include "Quake3ViewerExe.hpp"

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

#include "Quake3Viewer.hpp"

ALBA_IMPLEMENT_LOG_CATEGORY(Quake3ViewerDemo);

using namespace Alba::StringHashLiterals;

namespace Quake3ViewerExe
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
		// Register and Load modules
		//-----------------------------------------------------------------------------------------
		{
			//-------------------------------------------------------------------------------------
			// Register
			//-------------------------------------------------------------------------------------
			Alba::Core::RegisterModules();
			Alba::Graphics::RegisterModules();
			Alba::Framework::RegisterModules();
			Alba::Quake3Viewer::RegisterModules();

			//-------------------------------------------------------------------------------------
			// Load
			//-------------------------------------------------------------------------------------
			Alba::Core::ModuleRepository& moduleRepository = Alba::Core::ModuleRepository::Get();

			moduleRepository.LoadModule("Alba.Quake3Viewer"_nocasehash32);
		}

		//-----------------------------------------------------------------------------------------
		// Init application parameters
		//-----------------------------------------------------------------------------------------
		Alba::Framework::ApplicationInitParams initParams;
		Quake3ViewerExe::InitApplicationParams(initParams);

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

		const uint32 returnCode = application->Run();

		//-----------------------------------------------------------------------------------------
		// Shutdown
		//-----------------------------------------------------------------------------------------
		Alba::Framework::Shutdown();

		return returnCode;
	}

#endif

namespace Quake3ViewerExe
{
	using namespace Alba::BasicTypes;

	template <uint32 TValue> struct StaticNoCaseStringHash
	{
		static constexpr uint32 Value = TValue;
	};

	//---------------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------------
	void InitApplicationParams(Alba::Framework::ApplicationInitParams& anInitParamsOut)
	{
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