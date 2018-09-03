#pragma once

//-------------------------------------------------------------------------------------------------
// Name	:	Core_StringView.hpp
// Desc	:	Engine equivalent to std::stringview
//-------------------------------------------------------------------------------------------------

#include "Core.hpp"
#include <EASTL/string.h>
#include <EASTL/algorithm.h>

namespace Alba
{
	namespace StringViewLiterals = eastl::string_view_literals;

	namespace Core
	{
		template <typename TCharType>
		using BasicStringView = eastl::basic_string_view<TCharType>;

		typedef BasicStringView<char>		StringView;
		typedef BasicStringView<wchar_t>	WStringView;
		typedef BasicStringView<char16_t>	StringView16;
		typedef BasicStringView<char32_t>	StringView32;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		inline int CaseInsensitiveCompare(StringView aLeft, StringView aRight)
		{
			const size_t count = eastl::min(aLeft.length(), aRight.length());
			const int compare = eastl::CompareI(aLeft.data(), aRight.data(), count);

			return compare != 0 
					? compare
					: aLeft.length() < aRight.length() 
					? -1
					: aLeft.length() > aRight.length() 
					?  1 
					: 0;
		}
	}
}