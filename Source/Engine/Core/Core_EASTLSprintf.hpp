#pragma once

#include "Core_API.hpp"
#include "Core_Config.hpp"
#include "Core_BasicTypes.hpp"

namespace Alba
{
	namespace Core
	{
		struct Impl
		{
			static int Vsnprintf(char8_t* ALBA_RESTRICT aDestination, size_t count, const char8_t* ALBA_RESTRICT aFormat, va_list someArgs);
			static int Vsnprintf(char16_t* ALBA_RESTRICT aDestination, size_t count, const char16_t* ALBA_RESTRICT aFormat, va_list someArgs);
			static int Vsnprintf(char32_t* ALBA_RESTRICT aDestination, size_t count, const char32_t* ALBA_RESTRICT aFormat, va_list someArgs);
			static int Vsnprintf(wchar_t* ALBA_RESTRICT aDestination, size_t count, const wchar_t* ALBA_RESTRICT aFormat, va_list someArgs);
		};
	}
}

extern int Vsnprintf8(Alba::BasicTypes::char8_t*  pDestination, size_t n, const Alba::BasicTypes::char8_t*  pFormat, va_list arguments);
extern int Vsnprintf16(char16_t* pDestination, size_t n, const char16_t* pFormat, va_list arguments);
extern int Vsnprintf32(char32_t* pDestination, size_t n, const char32_t* pFormat, va_list arguments);

#if defined(EA_WCHAR_UNIQUE) && EA_WCHAR_UNIQUE
	extern int VsnprintfW(wchar_t* pDestination, size_t n, const wchar_t* pFormat, va_list arguments);
#endif

