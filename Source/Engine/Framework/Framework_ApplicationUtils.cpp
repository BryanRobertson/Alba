#include "Framework_Precompile.hpp"
#include "Framework.hpp"
#include "Framework_ApplicationUtils.hpp"
#include "Framework_GameApplication.hpp"

namespace Alba
{
	namespace Framework
	{
		namespace ApplicationUtils
		{
			//-----------------------------------------------------------------------------------------
			// Function prototypes
			//-----------------------------------------------------------------------------------------
			uint32 RunApplicationShared(InitParams&& anInitParams, Alba::Framework::FrameworkInitParams&& aFrameworkInitParams);

			//-----------------------------------------------------------------------------------------
			//-----------------------------------------------------------------------------------------
			#if defined(ALBA_PLATFORM_WINDOWS)

				uint32 RunApplication(InitParams&& anInitParams, HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/)
				{
					Alba::Framework::FrameworkInitParams frameworkInitParams;
					frameworkInitParams.myCommandLineParameters = Alba::Core::CommandLineParameters::CreateWindows();

					return RunApplicationShared(std::move(anInitParams), std::move(frameworkInitParams));
				}

			#else

				uint32 RunApplication(InitParams&& someInitParams, int argc, char** argv)
				{
					Alba::Framework::FrameworkInitParams frameworkInitParams;
					frameworkInitParams.myCommandLineParameters = Alba::Core::CommandLineParameters(argc, argv);

					eturn RunApplicationShared(std::move(anInitParams), std::move(frameworkInitParams));
				}

			#endif

			//-----------------------------------------------------------------------------------------
			//-----------------------------------------------------------------------------------------
			uint32 RunApplicationShared(InitParams&& anInitParams, Alba::Framework::FrameworkInitParams&& aFrameworkInitParams)
			{
				using Alba::Core::UniquePtr;
				using Alba::Core::StringHash32;
				using Alba::Framework::GameApplication;

				(void)anInitParams;
				(void)aFrameworkInitParams;

				//-----------------------------------------------------------------------------------------
				// Initialise framework
				//-----------------------------------------------------------------------------------------

				return 0;
			}
		}		
	}
}
