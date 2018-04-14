#include "Core_Precompile.hpp"
#include "Core.hpp"

//-------------------------------------------------------------------------------------------------
// Support for performance profiling
//-------------------------------------------------------------------------------------------------
#pragma warning(push, 3)
#include <Remotery.c>
#pragma warning(pop)

namespace Alba
{
	namespace Core
	{
		namespace ProfileInternal
		{
			Remotery* theRemoteryInstance = nullptr;

			void InitProfiling()
			{
				rmt_CreateGlobalInstance(&theRemoteryInstance);
			}

			void ShutDownProfiling()
			{
				rmt_DestroyGlobalInstance(theRemoteryInstance);
				theRemoteryInstance = nullptr;
			}
		}
	}
}