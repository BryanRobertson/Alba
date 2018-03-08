#pragma once

//-------------------------------------------------------------------------------------------------
// Asserts
//-------------------------------------------------------------------------------------------------
#if !defined(ALBA_RETAIL_BUILD)
	#if !defined(ALBA_DEBUG_ASSERTS_ENABLED)
		#define ALBA_DEBUG_ASSERTS_ENABLED	1
	#endif
#endif

//-------------------------------------------------------------------------------------------------
// Logging
//-------------------------------------------------------------------------------------------------
#if !defined(ALBA_RETAIL_BUILD)
	#if !defined(ALBA_DEBUG_LOGGING_ENABLED)
		#define ALBA_DEBUG_LOGGING_ENABLED	1
	#endif
#endif

//-------------------------------------------------------------------------------------------------
// Switch on string hash debugging in debug by default
//-------------------------------------------------------------------------------------------------
#if !defined(ALBA_DEBUG_STRINGHASH)
	#if !defined(ALBA_RETAIL_BUILD)
		#define ALBA_DEBUG_STRINGHASH
	#endif
#endif

//-------------------------------------------------------------------------------------------------
// EASTL configuration
//-------------------------------------------------------------------------------------------------
#define EASTL_EABASE_DISABLED

//-------------------------------------------------------------------------------------------------
// Compiler defines
//-------------------------------------------------------------------------------------------------
#if defined(_MSC_VER)
	#define ALBA_COMPILER_VISUALSTUDIO
	#define ALBA_RESTRICT __restrict

	#if defined(_CPPRTTI)
		#define	ALBA_RTTI_ENABLED 1
	#endif
#endif

