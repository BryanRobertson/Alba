#pragma once

#include "Core.hpp"
#include "Core_PlatformHeader.hpp"
#include "Core_Function.hpp"

namespace Alba
{
	namespace Core
	{
		#if defined(ALBA_PLATFORM_WINDOWS)

			//-----------------------------------------------------------------------------------------
			// Name	:	WindowEventHandler
			// Desc	:	Allows applications to handle events in the window event handler function
			//-----------------------------------------------------------------------------------------
			struct WindowEventHandler
			{
				//=====================================================================================
				// Public Types
				//=====================================================================================
				using HandlerFunc = FixedFunction<LRESULT(HWND, UINT, WPARAM, LPARAM)>;

				//=====================================================================================
				// Public Methods
				//=====================================================================================
				template <typename TObject>
				void Bind(TObject* anObject, LRESULT (TObject::*Handler)(HWND, UINT, WPARAM, LPARAM))
				{
					myHandlerFunc = [anObject, Handler](HWND aHwnd, UINT aMessage, WPARAM aWParam, LPARAM aLParam)
					{
						return (*anObject.*Handler)(aHwnd, aMessage, aWParam, aLParam);
					};
				}

				//=====================================================================================
				// Public Data Members
				//=====================================================================================
				HandlerFunc myHandlerFunc;
			};

		#endif
	}
}