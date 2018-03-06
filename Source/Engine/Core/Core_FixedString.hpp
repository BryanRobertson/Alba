//-------------------------------------------------------------------------------------------------
// Name	:	Core_FixedString.hpp
// Desc	:	Fixed-size string
//-------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include "Core_Container.hpp"
#include <EASTL/fixed_string.h>

namespace Alba
{
	namespace Core
	{
		//-------------------------------------------------------------------------------------------------
		// Name	:	Core::FixedBasicString
		// Desc	:	Fixed-size basic_string. If overflow is enabled, then the string is basically the same as Core_String
		//-------------------------------------------------------------------------------------------------
		template
		<
			typename TCharType,
			size_t	 TCount,
			OverflowBehavior TOverflowBehavior = OverflowBehavior::Allowed,
			typename TOverflowAllocator = EASTLAllocatorType
		>
		using FixedBasicString = eastl::fixed_string<TCharType, TCount, TOverflowBehavior == OverflowBehavior::Allowed, TOverflowAllocator>;

		//-------------------------------------------------------------------------------------------------
		// Name	:	Core::FixedString
		// Desc	:	Fixed-size string. If overflow is enabled, then the string is basically the same as Core_String
		//-------------------------------------------------------------------------------------------------
		template
		<
			size_t TCount,
			OverflowBehavior TOverflowBehavior = OverflowBehavior::Allowed,
			typename TOverflowAllocator = EASTLAllocatorType
		>
		using FixedString = FixedBasicString<char, TCount, TOverflowBehavior, TOverflowAllocator>;

		//-------------------------------------------------------------------------------------------------
		// Name	:	Core::FixedWString
		// Desc	:	Fixed-size wide-string. If overflow is enabled, then the string is basically the same as Core_String
		//-------------------------------------------------------------------------------------------------
		template
		<
			size_t TCount,
			OverflowBehavior TOverflowBehavior = OverflowBehavior::Allowed,
			typename TOverflowAllocator = EASTLAllocatorType
		>
		using FixedWString = FixedBasicString<wchar_t, TCount, TOverflowBehavior, TOverflowAllocator>;
	}
}
