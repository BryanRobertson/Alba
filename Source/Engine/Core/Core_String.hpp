#pragma once

//-------------------------------------------------------------------------------------------------
// Name	:	Core_String.hpp
// Desc	:	String types for the engine
//-------------------------------------------------------------------------------------------------

#include "Core_API.hpp"
#include <EASTL/string.h>

namespace Alba
{
	namespace Core
	{
		template <typename TCharType>
		using BasicString = eastl::basic_string<TCharType>;

		typedef BasicString<char>		String;
		typedef BasicString<wchar_t>	WString;
		typedef BasicString<char16_t>	UTF16String;
		typedef BasicString<char32_t>	UTF32String;
	}
}


