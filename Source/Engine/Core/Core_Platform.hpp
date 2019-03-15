#pragma once

#include "Core.hpp"
#include "Core_String.hpp"

#include <new>

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Hardware constant values
		//-----------------------------------------------------------------------------------------
		namespace HardwareConstants
		{
			//-----------------------------------------------------------------------------------------
			// Name: L1CacheLineSize
			// Desc: Constant that provides a good approximation the cache-line size on the current platform
			//-----------------------------------------------------------------------------------------
			constexpr size_t L1CacheLineSize = std::hardware_destructive_interference_size;
		}
		
		#if defined(ALBA_PLATFORM_WINDOWS)
			String GetLastErrorString();
		#endif
	}
}