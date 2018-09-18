//-------------------------------------------------------------------------------------------------
// Name		:	Input_API.hpp
// Desc		:	DLL-export boilerplate for Alba Input library
// Author	:	Bryan Robertson 
// Date		:	2018/17/09
//-------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------
// dllexport boilerplate
//-------------------------------------------------------------------------------------------------
#if defined(ALBA_INPUT_LIBRARY_DLL)
#   if defined(_MSC_VER)
#       if defined(ALBA_INPUT_LIBRARY_COMPILE)
#           define ALBA_INPUT_API __declspec(dllexport)
#       else
#           define ALBA_INPUT_API __declspec(dllimport)
#       endif
#   elif defined(__GNUC__) || defined(__clang__)
#       if defined(ALBA_INPUT_LIBRARY_COMPILE)
#           define ALBA_INPUT_API __attribute__ ((visibility ("default")))
#       endif
#   endif
#endif

#if !defined(ALBA_INPUT_API)
#   define ALBA_INPUT_API 
#endif
