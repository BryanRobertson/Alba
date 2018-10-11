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

		using String	= BasicString<char>;
		using WString	= BasicString<wchar_t>;
		using String16	= BasicString<char16_t>;
		using String32  = BasicString<char32_t>;
	}
}


