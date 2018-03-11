#include "GravityDemoExe_Precompile.hpp"
#include "GravityDemoExe.hpp"

#include "Core_CommandLineParameters.hpp"
#include "Core_Logging.hpp"
#include "Core_LogCategory.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_PlatformHeader.hpp"
#include "Core_Window.hpp"
#include "Core_UniquePtr.hpp"

ALBA_IMPLEMENT_LOG_CATEGORY(GravityDemo);

#if ALBA_PLATFORM_WINDOWS

	//-------------------------------------------------------------------------------------------------
	// WinMain
	//-------------------------------------------------------------------------------------------------
	int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
	{
		(void)hInstance;
		(void)hPrevInstance;
		(void)lpCmdLine;
		(void)nCmdShow;

		using Alba::Core::UniquePtr;

		Alba::Core::LogManager::CreateInstance();
		ALBA_LOG(GravityDemo, Alba::Core::LogLevel::Info, "Initialise application - commandLine: %s", lpCmdLine);

		Alba::Core::CommandLineParameters params(lpCmdLine);

		int windowPosX = 0;
		params.TryGetParamValue("windowPosX", windowPosX);

		int windowPosY = 0;
		params.TryGetParamValue("windowPosY", windowPosY);

		int windowWidth = 0;
		params.TryGetParamValue("windowWidth", windowWidth);

		int windowHeight = 0;
		params.TryGetParamValue("windowHeight", windowHeight);

		Alba::Core::FixedString<32> windowTitle;
		params.TryGetParamValue("windowTitle", windowTitle);

		Alba::Core::String stringTest;
		params.TryGetParamValue("windowTitle", stringTest);

		bool vsyncEnabled = false;
		if (params.IsParamPresent("enableVsync"))
		{
			params.TryGetParamValue("enableVsync", vsyncEnabled);
		}

		// Create window
		Alba::Core::WindowParams windowParams;
		windowParams.myPosition = Alba::Core::MakePair(windowPosX, windowPosY);
		windowParams.mySize = Alba::Core::MakePair(windowWidth, windowHeight);

		UniquePtr<Alba::Core::Window> window = Alba::Core::Window::Create();
		window->Init(windowParams);

		// Update
		while (window->Update())
		{

		}

		window.reset();

		//
		Alba::Core::LogManager::DestroyInstance();
		return 0;
	}

#endif