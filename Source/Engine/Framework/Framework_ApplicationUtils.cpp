#include "Framework_Precompile.hpp"
#include "Framework.hpp"
#include "Framework_ApplicationUtils.hpp"
#include "Framework_GameApplication.hpp"

#include "Core.hpp"
#include "Core_CommandLineModule.hpp"
#include "Core_CommandLineParameters.hpp"
#include "Core_Window.hpp"

#include "Graphics.hpp"

namespace Alba
{
	namespace Framework
	{
		namespace ApplicationUtils
		{
			//-----------------------------------------------------------------------------------------
			// Function prototypes
			//-----------------------------------------------------------------------------------------
			uint32 RunApplicationCommon(InitParams&& anInitParams, Alba::Framework::FrameworkInitParams&& aFrameworkInitParams);

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
				bool windowResizeEnabled = false;

				commandLine.TryGetParamValue("windowPosX"_nocasehash32, windowPosX);
				commandLine.TryGetParamValue("windowPosY"_nocasehash32, windowPosY);
				commandLine.TryGetParamValue("windowWidth"_nocasehash32, windowWidth);
				commandLine.TryGetParamValue("windowHeight"_nocasehash32, windowHeight);
				commandLine.TryGetParamValue("windowResizeEnabled"_nocasehash32, windowResizeEnabled);

				Alba::Core::WindowInitParams& windowParams = anInitParamsOut.myWindowInitParams;

				windowParams.myIsHidden = false;
				windowParams.myPositionX = windowPosX;
				windowParams.myPositionY = windowPosY;
				windowParams.mySizeX = windowWidth;
				windowParams.mySizeY = windowHeight;
				windowParams.myIsResizable = windowResizeEnabled;
			}

			//-----------------------------------------------------------------------------------------
			// Platform-specific run application
			//-----------------------------------------------------------------------------------------
			#if defined(ALBA_PLATFORM_WINDOWS)

				uint32 RunApplication(InitParams&& anInitParams, HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/)
				{
					Alba::Framework::FrameworkInitParams frameworkInitParams;
					frameworkInitParams.myCommandLineParameters = Alba::Core::CommandLineParameters::CreateWindows();

					return RunApplicationCommon(std::move(anInitParams), std::move(frameworkInitParams));
				}

			#endif

			uint32 RunApplication(InitParams&& someInitParams, int argc, char** argv)
			{
				Alba::Framework::FrameworkInitParams frameworkInitParams;
				frameworkInitParams.myCommandLineParameters = Alba::Core::CommandLineParameters(argc, argv);

				return RunApplicationCommon(std::move(someInitParams), std::move(frameworkInitParams));
			}

			//-----------------------------------------------------------------------------------------
			// Common init code
			//-----------------------------------------------------------------------------------------
			uint32 RunApplicationCommon(InitParams&& anInitParams, Alba::Framework::FrameworkInitParams&& aFrameworkInitParams)
			{
				using Alba::Core::UniquePtr;
				using Alba::Core::StringHash32;
				using Alba::Framework::GameApplication;

				//-----------------------------------------------------------------------------------------
				// Initialise framework
				//-----------------------------------------------------------------------------------------
				if (const uint32 result = Alba::Framework::Init(aFrameworkInitParams) != 0)
				{
					return result;
				}

				//-----------------------------------------------------------------------------------------
				// Register modules
				//-----------------------------------------------------------------------------------------
				{
					ALBA_LOG_INFO(Init, "---------------------------------------------------------------");
					ALBA_LOG_INFO(Init, "Register Modules")
					ALBA_LOG_INFO(Init, "---------------------------------------------------------------");

					//-------------------------------------------------------------------------------------
					// Register
					//-------------------------------------------------------------------------------------
					Alba::Core::RegisterModules();
					Alba::Graphics::RegisterModules();
					Alba::Framework::RegisterModules();

					if (anInitParams.myRegisterModulesCallback)
					{
						anInitParams.myRegisterModulesCallback();
					}

					ALBA_LOG_INFO(Init, "---------------------------------------------------------------");
				}

				//-----------------------------------------------------------------------------------------
				// Init application parameters
				//-----------------------------------------------------------------------------------------
				Alba::Framework::ApplicationInitParams initParams;
				InitApplicationParams(initParams);

				if (anInitParams.mySetupInitParamsCallback)
				{
					anInitParams.mySetupInitParamsCallback(initParams);
				}

				//-----------------------------------------------------------------------------------------
				// Create application
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
				// Load Main Module
				//-------------------------------------------------------------------------------------
				{
					Alba::Core::ModuleRepository& moduleRepository = Alba::Core::ModuleRepository::Get();
					if (!moduleRepository.LoadModule(anInitParams.myMainApplicationModuleNameId))
					{
						ALBA_LOG_ERROR(Init, "Failed to load main module \"%s\"", anInitParams.myMainApplicationModuleNameId.LogString().c_str());
						return 1;
					}
				}

				const uint32 returnCode = application->Run();

				//-----------------------------------------------------------------------------------------
				// Shutdown
				//-----------------------------------------------------------------------------------------
				ALBA_LOG_INFO(Shutdown, "Application Exiting with code %u", returnCode);
				Alba::Framework::Shutdown();

				return returnCode;
			}
		}
	}
}
