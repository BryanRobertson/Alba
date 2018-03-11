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
		// Initialise log
		//-----------------------------------------------------------------------------------------
		uint32 InitLog()
		{
			Alba::Core::LogManager::CreateInstance();

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		// Initialise Framework
		//-----------------------------------------------------------------------------------------
		uint32 Init(InitParams& /*aParams*/)
		{
			return 0;
		}

		//-----------------------------------------------------------------------------------------
		// Shutdown Framework
		//-----------------------------------------------------------------------------------------
		uint32 Shutdown()
		{
			return 0;
		}

		//-----------------------------------------------------------------------------------------
		// Shut down log
		//-----------------------------------------------------------------------------------------
		uint32 ShutdownLog()
		{
			Core::LogManager::DestroyInstance();

			return 0;
		}
	}
}
