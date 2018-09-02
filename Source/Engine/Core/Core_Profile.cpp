#include "Core_Precompile.hpp"
#include "Core.hpp"

//-------------------------------------------------------------------------------------------------
// Support for performance profiling
//-------------------------------------------------------------------------------------------------
#pragma warning(push, 3)
#include <Remotery.c>
#pragma warning(pop)

#ifdef ALBA_PROFILING_ENABLED

namespace Alba
{
	namespace Core
	{
		namespace ProfileInternal
		{
			Remotery* theRemoteryInstance = nullptr;

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			ALBA_CORE_API uint32 theProfilerFrameIndex = 0;
			ALBA_CORE_API bool theProfilerEnabled = false;

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			bool IsProfilerEnabled()
			{
				return theProfilerEnabled;
			}

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			void InitProfiling()
			{
				#if 0
				rmtSettings* settings = rmt_Settings();

				//-------------------------------------------------------------------------------------
				// Malloc
				//-------------------------------------------------------------------------------------
				settings->malloc = [](void* /*mm_context*/, rmtU32 size)
				{
					return Alba::Core::Malloc
					(
						size, 
						Alba::Core::DefaultAlignment, 
						0, 
						(Alba::Core::TAllocType)Alba::Core::AllocationType::CoreDebug, 
						"Profiler", 
						"", 
						0
					);
				};

				//-------------------------------------------------------------------------------------
				// Realloc
				//-------------------------------------------------------------------------------------
				settings->realloc = [](void* /*mm_context*/, void* ptr, rmtU32 size)
				{
					return Alba::Core::Realloc(ptr, size, "", 0);
				};
			
				//-------------------------------------------------------------------------------------
				// Free
				//-------------------------------------------------------------------------------------
				settings->free = [](void* /*mm_context*/, void* ptr)
				{
					Alba::Core::Free(ptr);
				};
				#endif

				theProfilerEnabled = true;
				rmt_CreateGlobalInstance(&theRemoteryInstance);
			}

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			void ShutDownProfiling()
			{
				if (theRemoteryInstance)
				{
					theProfilerEnabled = false;

					rmt_DestroyGlobalInstance(theRemoteryInstance);
					theRemoteryInstance = nullptr;
				}
			}
		}
	}
}

#endif