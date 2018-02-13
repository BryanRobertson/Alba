#pragma once

//-------------------------------------------------------------------------------------------------
// Name	:	Core_String.hpp
// Desc	"	String types for the engine
//-------------------------------------------------------------------------------------------------

#include "Core_API.hpp"
#include <EASTL/string.h>

template <typename TCharType>
using Core_BasicString = eastl::basic_string<TCharType>;

typedef Core_BasicString<char>		Core_String;
typedef Core_BasicString<wchar_t>	Core_WString;
typedef Core_BasicString<char16_t>	Core_UTF16String;
typedef Core_BasicString<char32_t>	Core_UTF32String;

