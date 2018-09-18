#include "Core_Precompile.hpp"
#include "Core_WindowModule.hpp"
#include "Core_Window.hpp"
#include "Core_PlatformHeader.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool WindowModule::OnLoad(Core::AnyDictionary /*someLoadParams*/)
		{
			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void WindowModule::OnUnload()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Window* WindowModule::GetWindow(void* aWindowHandle)
		{
			auto itr = myWindows.find(static_cast<HWND>(aWindowHandle));
			return itr != myWindows.end() ? itr->second : nullptr;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void WindowModule::RegisterWindow(Window& aWindow)
		{
			#if defined(ALBA_PLATFORM_WINDOWS)
			{
				const HWND windowHandle = aWindow.GetPlatformData().Get<HWND>();
				myWindows.emplace(windowHandle, &aWindow);
			}
			#else
			{
				(void)aWindow;
			}
			#endif
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void WindowModule::UnregisterWindow(Window& aWindow)
		{
			#if defined(ALBA_PLATFORM_WINDOWS)
			{
				const HWND windowHandle = aWindow.GetPlatformData().Get<HWND>();
				myWindows.erase(windowHandle);
			}
			#else
			{
				(void)aWindow;
			}
			#endif
		}
	}
}