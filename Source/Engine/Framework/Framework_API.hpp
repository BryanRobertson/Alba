//-------------------------------------------------------------------------------------------------
// Name		:	Framework_API.hpp
// Desc		:	DLL-export boilerplate for Alba Framework library
// Author	:	Bryan Robertson 
// Date		:	2018/02/17
//-------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------
// dllexport boilerplate
//-------------------------------------------------------------------------------------------------
#if defined(ALBA_FRAMEWORK_LIBRARY_DLL)
#   if defined(_MSC_VER)
#       if defined(ALBA_FRAMEWORK_LIBRARY_COMPILE)
#           define ALBA_FRAMEWORK_API __declspec(dllexport)
#       else
#           define ALBA_FRAMEWORK_API __declspec(dllimport)
#       endif
#   elif defined(__GNUC__) || defined(__clang__)
#       if defined(ALBA_FRAMEWORK_LIBRARY_COMPILE)
#           define ALBA_FRAMEWORK_API __attribute__ ((visibility ("default")))
#       endif
#   endif
#endif

#if !defined(ALBA_FRAMEWORK_API)
#   define ALBA_FRAMEWORK_API 
#endif
