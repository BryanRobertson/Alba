#pragma once

//-------------------------------------------------------------------------------------------------
// Name	:	Core_StringView.hpp
// Desc	:	Engine equivalent to std::stringview
//-------------------------------------------------------------------------------------------------

#include "Core.hpp"
#include <EASTL/string.h>

namespace Alba
{
	namespace Core
	{
		template <typename TCharType>
		using BasicStringView = eastl::basic_string_view<TCharType>;

		typedef BasicStringView<char>		StringView;
		typedef BasicStringView<wchar_t>	WStringView;
		typedef BasicStringView<char16_t>	StringView16;
		typedef BasicStringView<char32_t>	StringView32;
	}
}