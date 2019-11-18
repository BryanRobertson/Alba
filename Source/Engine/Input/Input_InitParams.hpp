#pragma once

#include "Core.hpp"
#include "Core_AnyDictionary.hpp"
#include "Input_API.hpp"

namespace Alba
{
	namespace Input
	{
		//-----------------------------------------------------------------------------------------------
		// Name	:	InitParams
		// Desc:	Initialisation parameters for the framework
		//-----------------------------------------------------------------------------------------------
		struct InitParams
		{
			// Platform specific data
			Core::AnyDictionary		myPlatformData;
		};
	}
}