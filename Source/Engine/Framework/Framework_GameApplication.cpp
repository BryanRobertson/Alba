#include "Framework_Precompile.hpp"
#include "Framework_GameApplication.hpp"
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
			using namespace Alba::Literals;

			Alba::Core::ModuleRepository& moduleRepository = Alba::Core::ModuleRepository::Get();

			//----------------------------------------------------------------------
			// Initialise profiling, unless explicitly disabled on the commandline
			//----------------------------------------------------------------------
			{
				const Alba::Core::CommandLineParameters& commandLine = Alba::Core::CommandLineModule::Get().GetParams();

				bool disableProfiler = false;
				if (!commandLine.TryGetParamValue("disableProfiler"_nocasehash32, disableProfiler) || !disableProfiler)
				{
					ALBA_PROFILE_INIT();
					ALBA_PROFILE_SETCURRENTTHREADNAME("Main Thread");
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
				Core::AnyDictionary initParamsDict;

				Alba::Graphics::InitParams graphicsInitParams;
				graphicsInitParams.myWindowWidth = anInitParams.myWindowInitParams.mySize.x();
				graphicsInitParams.myWindowHeight = anInitParams.myWindowInitParams.mySize.y();
				InitGraphicsPlatformData(graphicsInitParams.myPlatformData);

				initParamsDict.Set(graphicsInitParams);

				if ( !moduleRepository.LoadModule("Alba.Graphics"_nocasehash32, initParamsDict) )
				{
					return 1;
				}

				Alba::Graphics::GraphicsModule& graphicsModule = Alba::Graphics::GraphicsModule::Get();
				myGraphicsService = &graphicsModule.GetGraphicsServiceMutable();
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
			
			myGraphicsService->ClearBuffer(Math::Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GameApplication::Render()
		{
			ALBA_PROFILE_SCOPED(Render);

			{
				ALBA_PROFILE_SCOPED(Present);
				myGraphicsService->Present();

				using namespace std::literals;
				Alba::Core::ThisThread::sleep_for(10ms);
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