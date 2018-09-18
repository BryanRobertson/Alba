#pragma once

#include "Core.hpp"
#include "Core_Module.hpp"
#include "Core_StringView.hpp"
#include "Core_VectorMap.hpp"

namespace Alba
{
	namespace Core
	{
		class Window;

		//-----------------------------------------------------------------------------------------
		// Name	:	WindowModule
		// Desc	:	Module that allows the application windows to be accessed from other parts
		//			of the application
		//-----------------------------------------------------------------------------------------
		class ALBA_CORE_API WindowModule final : public Core::Module<WindowModule>
		{
			public:

				friend class Window;

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static constexpr StringView GetModuleName()
				{
					return "Alba.Window";
				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				bool		OnLoad(Core::AnyDictionary someLoadParams);
				void		OnUnload();

				//---------------------------------------------------------------------------------
				// Access windows
				//---------------------------------------------------------------------------------

				// Get a pointer to a window from a platform window handle (HWND on Windows)
				// DO NOT hold on to a pointer to the window!
				Window*		GetWindow(void* aPlatformWindowHandle);

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				void		RegisterWindow(Window& aWindow);
				void		UnregisterWindow(Window& aWindow);

				//=================================================================================
				// Private Data
				//=================================================================================
				VectorMap<void*, Window*> myWindows;
		};
	}
}
