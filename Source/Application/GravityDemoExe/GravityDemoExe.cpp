#include "GravityDemoExe_Precompile.hpp"
#include "GravityDemoExe.hpp"

#include "Core_CommandLineParameters.hpp"

#if ALBA_PLATFORM_WINDOWS
#include <Windows.h>

	//-------------------------------------------------------------------------------------------------
	// WinMain
	//-------------------------------------------------------------------------------------------------
	int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
	{
		(void)hInstance;
		(void)hPrevInstance;
		(void)lpCmdLine;
		(void)nCmdShow;

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

		Alba::Core::String test;
		params.TryGetParamValue("windowTitle", test);
		
		return 0;
	}

#endif