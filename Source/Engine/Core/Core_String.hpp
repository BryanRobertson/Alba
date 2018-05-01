#pragma once

//-------------------------------------------------------------------------------------------------
// Name	:	Core_String.hpp
// Desc	:	String types for the engine
//-------------------------------------------------------------------------------------------------

#include "Core.hpp"
#include <EASTL/string.h>

namespace Alba
{
	namespace Core
	{
		template <typename TCharType, typename TAllocator = EASTLAllocatorType>
		using BasicString = eastl::basic_string<TCharType, TAllocator>;

		typedef BasicString<char>		String;
		typedef BasicString<wchar_t>	WString;
		typedef BasicString<char16_t>	String16;
		typedef BasicString<char32_t>	String32;
	}
}


