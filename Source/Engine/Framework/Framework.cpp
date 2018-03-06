#include "Framework_Precompile.hpp"
#include "Framework.hpp"
#include "Core_Memory_Impl.hpp"
#include "Core_Logging.hpp"
#include "Core_LogCategory.hpp"

namespace Alba
{
	namespace Framework
	{
		//-----------------------------------------------------------------------------------------
		// Initialise Framework
		//-----------------------------------------------------------------------------------------
		uint32 Init(InitParams& /*aParams*/)
		{
			//------------------------------------------------------------------------
			// Initialise log manager
			//------------------------------------------------------------------------
			Alba::Core::LogManager::CreateInstance();

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		// Shutdown Framework
		//-----------------------------------------------------------------------------------------
		uint32 Shutdown()
		{
			//------------------------------------------------------------------------
			// Destroy log manager
			//------------------------------------------------------------------------
			Alba::Core::LogManager::DestroyInstance();

			return 0;
		}
	}
}
