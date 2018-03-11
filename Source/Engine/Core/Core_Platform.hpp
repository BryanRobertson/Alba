#pragma once

#include "Core.hpp"
#include "Core_String.hpp"

namespace Alba
{
	namespace Core
	{
		#if defined(ALBA_PLATFORM_WINDOWS)
			String GetLastErrorString();
		#endif	
	}
}