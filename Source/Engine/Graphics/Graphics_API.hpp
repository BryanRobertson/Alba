//-------------------------------------------------------------------------------------------------
// Name		:	Graphics_API.hpp
// Desc		:	DLL-export boilerplate for Alba Graphics library
// Author	:	Bryan Robertson 
// Date		:	2017/11/25
//-------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------
// dllexport boilerplate
//-------------------------------------------------------------------------------------------------
#if defined(ALBA_GRAPHICS_LIBRARY_DLL)
#   if defined(_MSC_VER)
#       if defined(ALBA_GRAPHICS_LIBRARY_COMPILE)
#           define ALBA_GRAPHICS_API __declspec(dllexport)
#       else
#           define ALBA_GRAPHICS_API __declspec(dllimport)
#       endif
#   elif defined(__GNUC__) || defined(__clang__)
#       if defined(ALBA_GRAPHICS_LIBRARY_COMPILE)
#           define ALBA_GRAPHICS_API __attribute__ ((visibility ("default")))
#       endif
#   endif
#endif

#if !defined(ALBA_GRAPHICS_API)
#   define ALBA_GRAPHICS_API 
#endif
