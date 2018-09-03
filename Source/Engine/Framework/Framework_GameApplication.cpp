#include "Framework_Precompile.hpp"
#include "Framework_GameApplication.hpp"
#include "Framework_Debug.hpp"
#include "Graphics_InitParams.hpp"
#include "Graphics_Module.hpp"
#include "Graphics_Service.hpp"
#include "Core_Memory.hpp"
#include "Core_Pair.hpp"
#include "Core_Window.hpp"
#include "Core_WindowEventHandler.hpp"
#include "Core_Profile.hpp"
#include "Core_CommandLineModule.hpp"
#include "Core_CommandLineParameters.hpp"

#ifdef CreateWindow
	#undef CreateWindow
#endif

namespace Alba
{
	namespace Framework
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ Core::UniquePtr<GameApplication> GameApplication::Create()
		{
			return Core::UniquePtr<GameApplication>
			(
				ALBA_NEW(Core::AllocationType::Framework, "GameApplication") GameApplication()
			);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		GameApplication::GameApplication()
			: myQuit(false)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		GameApplication::~GameApplication()
		{
			if (myWindow)
			{
				Shutdown();
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 GameApplication::Init(ApplicationInitParams anInitParams)
		{
			using namespace Alba::StringHashLiterals;

			Alba::Core::ModuleRepository& moduleRepository = Alba::Core::ModuleRepository::Get();

			const Alba::Core::CommandLineParameters& commandLine = Alba::Core::CommandLineModule::Get().GetParams();

			//----------------------------------------------------------------------
			// Initialise profiling, unless explicitly disabled on the commandline
			//----------------------------------------------------------------------
			{
				bool disableProfiler = false;
				if (!commandLine.TryGetParamValue("disableProfiler"_nocasehash32, disableProfiler) || !disableProfiler)
				{
					ALBA_PROFILE_INIT();
					ALBA_PROFILE_SETCURRENTTHREADNAME("Main Thread");

					ALBA_LOG_INFO(Framework, "Profiler initialised");
				}
			}

			//----------------------------------------------------------------------
			// Initialise application
			//----------------------------------------------------------------------
			{
				myInitParams = std::move(anInitParams);
				CreateWindow(myInitParams.myWindowInitParams);
			}

			//----------------------------------------------------------------------
			// Initialise graphics
			//----------------------------------------------------------------------
			{
				Alba::Graphics::InitParams graphicsInitParams;

				// Allow ImGui to be disabled on the commandline
				bool disableImGui = false;
				if (commandLine.TryGetParamValue("disableImGui"_nocasehash32, disableImGui))
				{
					graphicsInitParams.myEnableImGui = false;
				}
				
				graphicsInitParams.myWindowWidth = anInitParams.myWindowInitParams.mySizeX;
				graphicsInitParams.myWindowHeight = anInitParams.myWindowInitParams.mySizeY;
				InitGraphicsPlatformData(graphicsInitParams.myPlatformData);

				if ( !moduleRepository.LoadModule("Alba.Graphics"_nocasehash32, std::move(graphicsInitParams)) )
				{
					return 1;
				}

				Alba::Graphics::GraphicsModule& graphicsModule = Alba::Graphics::GraphicsModule::Get();
				myGraphicsService = &graphicsModule.GetGraphicsServiceMutable();

				// Load ImGui/Console unless specifically disabled
				if (graphicsInitParams.myEnableImGui)
				{
					// Load ImGui module
					moduleRepository.LoadModule("Alba.Graphics.ImGui"_nocasehash32);

					// Load console module
					moduleRepository.LoadModule("Alba.Graphics.Console"_nocasehash32);
				}			
			}

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GameApplication::InitGraphicsPlatformData(Core::AnyDictionary& aPlatformDataOut)
		{
			aPlatformDataOut = myWindow->GetPlatformData();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 GameApplication::Run()
		{
			myTimer.Reset();

			//-------------------------------------------------------------------------------------
			// Update
			//-------------------------------------------------------------------------------------
			myQuit = false;
			while (!myQuit)
			{
				Update();
			}

			//-------------------------------------------------------------------------------------
			// Shutdown
			//-------------------------------------------------------------------------------------
			Shutdown();

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GameApplication::Update()
		{
			ALBA_PROFILE_BEGINFRAME();

			{
				// Update timer
				myTimer.Update();

				//-----------------------------------------------------------------------------------------
				// Begin Frame
				//-----------------------------------------------------------------------------------------
				{
					BeginFrame();
				}

				//-----------------------------------------------------------------------------------------
				// Update Window
				//-----------------------------------------------------------------------------------------
				{
					ALBA_PROFILE_SCOPED(WindowUpdate);
					myWindow->Update();
				}

				//-----------------------------------------------------------------------------------------
				// Update Modules
				//-----------------------------------------------------------------------------------------
				{
					Alba::Core::ModuleRepository& moduleRepository = Alba::Core::ModuleRepository::Get();
					moduleRepository.Update(myTimer);
				}

				//-----------------------------------------------------------------------------------------
				// Render
				//-----------------------------------------------------------------------------------------
				{
					Render();
				}

				//-----------------------------------------------------------------------------------------
				// End Frame
				//-----------------------------------------------------------------------------------------
				{
					EndFrame();
				}
			}

			ALBA_PROFILE_ENDFRAME();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GameApplication::BeginFrame()
		{
			ALBA_PROFILE_SCOPED(BeginFrame);
			
			myGraphicsService->BeginFrame();
			myGraphicsService->ClearBuffer(Math::Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GameApplication::Render()
		{
			ALBA_PROFILE_SCOPED(Render);

			{
				ALBA_PROFILE_SCOPED(Present);
				myGraphicsService->EndFrame();

				//using namespace std::literals;
				//Alba::Core::ThisThread::sleep_for(5ms);
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GameApplication::EndFrame()
		{
			ALBA_PROFILE_SCOPED(EndFrame);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 GameApplication::Shutdown()
		{
			// Destroy window
			myWindow.reset();

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GameApplication::Quit()
		{
			myQuit = true;
		}
	}
}