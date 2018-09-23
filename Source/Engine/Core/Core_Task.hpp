#pragma once

#include "Core.hpp"
#include "Core_Thread.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		struct Task
		{
			//=====================================================================================
			// Public Data
			//=====================================================================================

			uint32	myId;
			uint32	myParent;
			uint32	myDependsOn;

			//char myBuffer[std::hardware_destructive_interference_size];
		};
	}
}