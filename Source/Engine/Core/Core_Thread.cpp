#include "Core_Precompile.hpp"
#include "Core_Thread.hpp"

#include "Core_PlatformHeader.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void YieldCPU()
		{
			#if ALBA_PLATFORM_WINDOWS
				::YieldProcessor();
			#endif
		}
	}
}