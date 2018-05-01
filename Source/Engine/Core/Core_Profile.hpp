#pragma once

#include "Core.hpp"
#include "Core_StringUtils.hpp"

//-------------------------------------------------------------------------------------------------
// Support for performance profiling
//-------------------------------------------------------------------------------------------------
#ifdef ALBA_PROFILING_ENABLED

	#define RMT_ENABLED         1           // Disable this to not include any bits of Remotery in your build
	#define RMT_USE_TINYCRT     0           // Used by the Celtoys TinyCRT library(not released yet)
	#define RMT_USE_CUDA        0           // Assuming CUDA headers / libs are setup, allow CUDA profiling
	#define RMT_USE_D3D11       0           // Assuming Direct3D 11 headers / libs are setup, allow D3D11 GPU profiling
	#define RMT_USE_OPENGL      0           // Allow OpenGL GPU profiling(dynamically links OpenGL libraries on available platforms)
	#define RMT_USE_METAL       0           // Allow Metal profiling of command buffers

	#pragma warning(push, 3)
	#include <Remotery.h>
	#pragma warning(pop)

	//---------------------------------------------------------------------------------------------
	// Call at the start of the application to initialise the profiling system
	//---------------------------------------------------------------------------------------------
	#define ALBA_PROFILE_INIT()	::Alba::Core::ProfileInternal::InitProfiling()

	//---------------------------------------------------------------------------------------------
	// Log Text
	//---------------------------------------------------------------------------------------------
	#define ALBA_PROFILE_LOGTEXT(aLogString)			rmt_LogText(aLogString)		

	//---------------------------------------------------------------------------------------------
	// Scoped profile 
	//---------------------------------------------------------------------------------------------
	#define ALBA_PROFILE_SCOPED(anId)				rmt_ScopedCPUSample(anId, 0)

	//---------------------------------------------------------------------------------------------
	// Scoped profile - Search parent for profiles with the same name and aggregate into one timer
	//---------------------------------------------------------------------------------------------
	#define ALBA_PROFILE_SCOPED_AGGREGATE(anId)		rmt_ScopedCPUSample(anId, RMTSF_Aggregate)

	//---------------------------------------------------------------------------------------------
	// Scoped profile - Use for recursive functions to merge into a single timer
	//---------------------------------------------------------------------------------------------
	#define ALBA_PROFILE_SCOPED_RECURSIVE(anId)		rmt_ScopedCPUSample(anId, RMTSF_Recursive)

	//---------------------------------------------------------------------------------------------
	// Function profile 
	//---------------------------------------------------------------------------------------------
	//#define ALBA_PROFILE_FUNCTION()					rmt_ScopedCPUSample(__FUNCTION__, 0)

	//---------------------------------------------------------------------------------------------
	// Function profile - Use for recursive functions to merge into a single timer
	//---------------------------------------------------------------------------------------------
	//#define ALBA_PROFILE_FUNCTION_RECURSIVE()		rmt_ScopedCPUSample(__FUNCTION__, RMTSF_Recursive)

	//---------------------------------------------------------------------------------------------
	// Manual profile begin/end
	//---------------------------------------------------------------------------------------------
	#define ALBA_PROFILE_BEGIN(anId)				rmt_BeginCPUSample(anId, 0)
	#define ALBA_PROFILE_END(anId)					rmt_EndCPUSample()

	#define ALBA_PROFILE_BEGIN_AGGREGATE(anId)		rmt_BeginCPUSample(anId, RMTSF_Aggregate)
	#define ALBA_PROFILE_END_AGGREGATE(anId)		rmt_EndCPUSample()

	#define ALBA_PROFILE_BEGIN_RECURSIVE(anId)		rmt_BeginCPUSample(anId, RMTSF_Recursive)
	#define ALBA_PROFILE_END_RECURSIVE(anId)		rmt_EndCPUSample()

	//---------------------------------------------------------------------------------------------
	// Begin frame
	//---------------------------------------------------------------------------------------------
	#define ALBA_PROFILE_BEGINFRAME()																	\
		RMT_OPTIONAL																					\
		(																								\
			RMT_ENABLED,																				\
			{																							\
				static char buffer[128];																\
				std::snprintf(buffer, 64, "%u", Alba::Core::ProfileInternal::theProfilerFrameIndex);	\
																										\
				++Alba::Core::ProfileInternal::theProfilerFrameIndex;									\
				_rmt_BeginCPUSample(buffer, 0, &::Alba::Core::ProfileInternal::theProfilerFrameIndex);	\
			}																							\
		);

	//---------------------------------------------------------------------------------------------
	// End frame
	//---------------------------------------------------------------------------------------------
	#define ALBA_PROFILE_ENDFRAME()					rmt_EndCPUSample()

	//---------------------------------------------------------------------------------------------
	// Set current thread name
	//---------------------------------------------------------------------------------------------
	#define ALBA_PROFILE_SETCURRENTTHREADNAME(aName) rmt_SetCurrentThreadName(aName)

	//---------------------------------------------------------------------------------------------
	// Shut down profiling
	//---------------------------------------------------------------------------------------------
	#define ALBA_PROFILE_SHUTDOWN()					::Alba::Core::ProfileInternal::ShutDownProfiling()

	namespace Alba
	{
		namespace Core
		{
			namespace ProfileInternal
			{
				extern ALBA_CORE_API void InitProfiling();
				extern ALBA_CORE_API void ShutDownProfiling();

				ALBA_CORE_API extern uint32 theProfilerFrameIndex;
			}
		}
	}

#else
	#define ALBA_PROFILE_INIT()
	#define ALBA_PROFILE_LOGTEXT(aLogString)
	#define ALBA_PROFILE_BEGINFRAME()
	#define ALBA_PROFILE_ENDFRAME()
	#define ALBA_PROFILE_SCOPED(anId)
	#define ALBA_PROFILE_SCOPED_AGGREGATE(anId)	
	#define ALBA_PROFILE_SCOPED_RECURSIVE(anId)
	//#define ALBA_PROFILE_FUNCTION()
	//#define ALBA_PROFILE_FUNCTION_RECURSIVE()
	#define ALBA_PROFILE_BEGIN(anId)			
	#define ALBA_PROFILE_END(anId)				
	#define ALBA_PROFILE_BEGIN_AGGREGATE(anId)	
	#define ALBA_PROFILE_END_AGGREGATE(anId)	
	#define ALBA_PROFILE_BEGIN_RECURSIVE(anId)	
	#define ALBA_PROFILE_END_RECURSIVE(anId)	
	#define ALBA_PROFILE_SETCURRENTTHREADNAME(aName) 
	#define ALBA_PROFILE_SHUTDOWN()
#endif

