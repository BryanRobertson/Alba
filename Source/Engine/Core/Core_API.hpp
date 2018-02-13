//-------------------------------------------------------------------------------------------------
// Name		:	Core_API.hpp
// Desc		:	DLL-export boilerplate for Alba Core library
// Author	:	Bryan Robertson 
// Date		:	2017/11/25
//-------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------
// dllexport boilerplate
//-------------------------------------------------------------------------------------------------
#if defined(ALBA_CORE_LIBRARY_DLL)
#   if defined(_MSC_VER)
#       if defined(ALBA_CORE_LIBRARY_COMPILE)
#           define ALBA_CORE_API __declspec(dllexport)
#       else
#           define ALBA_CORE_API __declspec(dllimport)
#       endif
#   elif defined(__GNUC__) || defined(__clang__)
#       if defined(ALBA_CORE_LIBRARY_COMPILE)
#           define ALBA_CORE_API __attribute__ ((visibility ("default")))
#       endif
#   endif
#endif

#define ALBA_CDECL __cdecl

#if !defined(ALBA_CORE_API)
#   define ALBA_CORE_API 
#endif
