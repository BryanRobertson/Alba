#include "Core_Precompile.hpp"
#include "Core_EASTLSprintf.hpp"

#include <string>

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		int Impl::Vsnprintf(char8_t* ALBA_RESTRICT aDestination, size_t count, const char8_t* ALBA_RESTRICT aFormat, va_list someArgs)
		{
			return std::vsnprintf(aDestination, count, aFormat, someArgs);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		int Impl::Vsnprintf(char16_t* ALBA_RESTRICT aDestination, size_t count, const char16_t* ALBA_RESTRICT aFormat, va_list someArgs)
		{
#			if defined(ALBA_COMPILER_VISUALSTUDIO) && defined(ALBA_PLATFORM_WINDOWS)
				return _vsnwprintf_s((wchar_t*)aDestination, count, count, (wchar_t*)aFormat, someArgs);
			#else
				#pragma error("Not Implemented");
			#endif
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		int Impl::Vsnprintf(char32_t* ALBA_RESTRICT aDestination, size_t count, const char32_t* ALBA_RESTRICT aFormat, va_list someArgs)
		{
			#if defined(ALBA_COMPILER_VISUALSTUDIO) && defined(ALBA_PLATFORM_WINDOWS)
				return _vsnwprintf_s((wchar_t*)aDestination, count, count, (wchar_t*)aFormat, someArgs);
			#else
				#pragma error("Not Implemented");
			#endif
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		int Impl::Vsnprintf(wchar_t* ALBA_RESTRICT aDestination, size_t count, const wchar_t* ALBA_RESTRICT aFormat, va_list someArgs)
		{
			#if defined(ALBA_COMPILER_VISUALSTUDIO) && defined(ALBA_PLATFORM_WINDOWS)
				return _vsnwprintf_s((wchar_t*)aDestination, count, count, (wchar_t*)aFormat, someArgs);
			#else
				#pragma error("Not Implemented");
			#endif
		}
	}
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
int Vsnprintf8(char8_t*  pDestination, size_t n, const char8_t*  pFormat, va_list arguments)
{
	return ::Alba::Core::Impl::Vsnprintf(pDestination, n, pFormat, arguments);
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
int Vsnprintf16(char16_t* pDestination, size_t n, const char16_t* pFormat, va_list arguments)
{
	return ::Alba::Core::Impl::Vsnprintf(pDestination, n, pFormat, arguments);
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
int Vsnprintf32(char32_t* pDestination, size_t n, const char32_t* pFormat, va_list arguments)
{
	return ::Alba::Core::Impl::Vsnprintf(pDestination, n, pFormat, arguments);
}

//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
#if defined(EA_WCHAR_UNIQUE) && EA_WCHAR_UNIQUE
	int VsnprintfW(wchar_t* pDestination, size_t n, const wchar_t* pFormat, va_list arguments)
	{
		return ::Alba::Core::Impl::Vsnprintf(pDestination, n, pFormat, arguments);
	}
#endif
