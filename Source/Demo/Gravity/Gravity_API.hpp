//-------------------------------------------------------------------------------------------------
// Name		:	Framework_API.hpp
// Desc		:	DLL-export boilerplate for Alba Gravity demo library
// Author	:	Bryan Robertson 
// Date		:	2018/02/27
//-------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------
// dllexport boilerplate
//-------------------------------------------------------------------------------------------------
#if defined(ALBA_GRAVITY_LIBRARY_DLL)
#   if defined(_MSC_VER)
#       if defined(ALBA_GRAVITY_LIBRARY_COMPILE)
#           define ALBA_GRAVITY_API __declspec(dllexport)
#       else
#           define ALBA_GRAVITY_API __declspec(dllimport)
#       endif
#   elif defined(__GNUC__) || defined(__clang__)
#       if defined(ALBA_GRAVITY_LIBRARY_COMPILE)
#           define ALBA_GRAVITY_API __attribute__ ((visibility ("default")))
#       endif
#   endif
#endif

#if !defined(ALBA_GRAVITY_API)
#   define ALBA_GRAVITY_API 
#endif

namespace Alba
{
	namespace BasicTypes
	{

	}

	namespace Framework
	{
		using namespace Alba::BasicTypes;
	}
}