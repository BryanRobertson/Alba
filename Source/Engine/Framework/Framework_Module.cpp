#include "Framework_Precompile.hpp"
#include "Framework_Module.hpp"
#include "Framework_InitParams.hpp"
#include "Core_Window.hpp"

namespace Alba
{
	namespace Framework
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void FrameworkModule::OnRegister()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void FrameworkModule::OnUnregister()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool FrameworkModule::OnLoad(const Core::AnyDictionary& someParams)
		{
			const InitParams* initParams = someParams.GetPtr<InitParams>();

			const int windowPosX	= initParams ? initParams->myWindowPosX : 100;
			const int windowPosY	= initParams ? initParams->myWindowPosY : 100;
			const uint windowWidth	= initParams ? initParams->myWindowWidth : 800;
			const uint windowHeight = initParams ? initParams->myWindowHeight : 600;

			// Create window
			Alba::Core::WindowParams windowParams;
			windowParams.myPosition = Alba::Core::MakePair(windowPosX, windowPosY);
			windowParams.mySize = Alba::Core::MakePair(windowWidth, windowHeight);

			ourApplicationWindow = Alba::Core::Window::Create();
			if (!ourApplicationWindow->Init(windowParams))
			{
				ALBA_LOG_ERROR(FrameworkLog, "Failed to create window!");
				return 1;
			}

			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void FrameworkModule::OnUnload()
		{
			ourApplicationWindow.reset();
		}
	}
}