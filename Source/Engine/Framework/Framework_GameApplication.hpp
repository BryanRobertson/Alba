#pragma once

#include "Framework_API.hpp"
#include "Core_Config.hpp"
#include "Core_String.hpp"
#include "Core_FixedString.hpp"
#include "Core_Window.hpp"

#ifdef CreateWindow
	#undef CreateWindow
#endif

namespace Alba
{
	namespace Graphics
	{
		struct PlatformData;
		class GraphicsService;
	}

	namespace Input
	{
		class InputService;
	}

	namespace Framework
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	ApplicationInitParams
		//-----------------------------------------------------------------------------------------
		struct ALBA_FRAMEWORK_API ApplicationInitParams
		{
			Alba::Core::WindowInitParams myWindowInitParams;
		};

		struct ApplicationInitParams;

		//-----------------------------------------------------------------------------------------
		// Name	:	GameApplication
		// Desc	:	Game application class. 
		//			Encapsulates initialisation, update, shutdown, etc.
		//-----------------------------------------------------------------------------------------
		class ALBA_FRAMEWORK_API GameApplication final
		{
			public:

				friend struct GameWindowEventHandlerImpl;

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static Core::UniquePtr<GameApplication> Create();

				//=================================================================================
				// Public Constructors
				//=================================================================================
				GameApplication();
				~GameApplication();

				//=================================================================================
				// Public Methods
				//=================================================================================
				uint32		Init(ApplicationInitParams anInitParams);
				uint32		Run();
				uint32		Shutdown();

				void		Quit();

				//---------------------------------------------------------------------------------
				// Accessors
				//---------------------------------------------------------------------------------
				bool				HasWindow() const;
				const Core::Window&	GetWindow() const;

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				void		BeginFrame();
				void		Update();
				void		Render();
				void		EndFrame();

				uint32		CreateWindow(const Core::WindowInitParams& aWindowInitParams);
				void		GetPlatformData(Core::AnyDictionary& aPlatformDataOut);

				//=================================================================================
				// Private Data
				//=================================================================================
				Core::UniquePtr<Core::Window>		myWindow;
				Alba::Graphics::GraphicsService*	myGraphicsService = nullptr;
				Alba::Input::InputService*			myInputService = nullptr;

				ApplicationInitParams				myInitParams;
				Core::Time							myTimer;
				bool								myQuit = false;
		};
	}
}
