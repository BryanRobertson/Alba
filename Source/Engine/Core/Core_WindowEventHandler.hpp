#pragma once

#include "Core.hpp"
#include "Core_PlatformHeader.hpp"
#include "Core_Function.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	WindowEventHandler
		// Desc	:	Allows applications to handle events in the window event handler function
		//-----------------------------------------------------------------------------------------
		struct WindowEventHandler
		{
			//=====================================================================================
			// Public Types
			//=====================================================================================
			typedef FixedFunction<LRESULT(HWND, UINT, WPARAM, LPARAM)> HandlerFunc;

			//=====================================================================================
			// Public Methods
			//=====================================================================================
			template <typename TObject>
			void Bind(TObject* anObject, LRESULT (TObject::*Handler)(HWND, UINT, WPARAM, LPARAM))
			{
				using std::placeholders::_1;
				using std::placeholders::_2;
				using std::placeholders::_3;
				using std::placeholders::_4;

				myHandlerFunc = std::bind(Handler, anObject, _1, _2, _3, _4);
			}

			//=====================================================================================
			// Public Data Members
			//=====================================================================================
			HandlerFunc myHandlerFunc;
		};
	}
}