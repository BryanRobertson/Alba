#pragma once

//-------------------------------------------------------------------------------------------------
// Name      : Core_Assert.hpp
// Desc      : Debug assert macros
// Author    : Bryan Robertson
// Date      : 2018/02/28
//-------------------------------------------------------------------------------------------------
#include "Core_Config.hpp"

#if defined(ALBA_COMPILER_VISUALSTUDIO)
	#define ALBA_DEBUG_BREAK()	__debugbreak()	
#else
	#define ALBA_DEBUG_BREAK()
#endif

#if defined(ALBA_DEBUG_ASSERTS_ENABLED)
	#define ALBA_ASSERT_FAILED(anAssertCond, ...)	ALBA_DEBUG_BREAK();
	#define ALBA_ASSERT(anAssertCond, ...) do { if (anAssertCond) { ALBA_ASSERT_FAILED(anAssertCond, __VA_ARGS__); }  } while (0)
#else
	#define ALBA_ASSERT_FAILED(anAssertCond, ...)	
	#define ALBA_ASSERT(anAssertCond, ...)
#endif