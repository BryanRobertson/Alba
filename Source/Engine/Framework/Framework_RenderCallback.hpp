#pragma once

#include "Framework_API.hpp"
#include "Core_Function.hpp"
#include "Core_Config.hpp"

namespace Alba
{
	namespace Core { class Window;  }

	namespace Framework
	{
		typedef uint64 ViewportId;

		//-----------------------------------------------------------------------------------------
		// Name	:	RenderCallback
		// Desc	:	Callback type for render function called on a viewport by the engine
		//-----------------------------------------------------------------------------------------
		typedef void(*RenderCallback)(const Core::Window& aWindow, ViewportId anId, uint16 aWidth, uint16 aHeight);
	}
}