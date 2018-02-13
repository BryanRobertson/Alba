//-------------------------------------------------------------------------------------------------
// Name	:	Core_FixedString.hpp
// Desc	:	Fixed-size string
//-------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include "Core_Container.hpp"
#include <EASTL/fixed_string.h>

//-------------------------------------------------------------------------------------------------
// Name	:	Core_FixedBasicString
// Desc	:	Fixed-size basic_string. If overflow is enabled, then the string is basically the same as Core_String
//-------------------------------------------------------------------------------------------------
template
<
	typename TCharType,
	size_t	 TCount,
	Core_OverflowBehavior TOverflowBehavior = Core_OverflowBehavior::Allowed,
	typename TOverflowAllocator = EASTLAllocatorType
>
using Core_FixedBasicString = eastl::fixed_string<TCharType, TCount, TOverflowBehavior == Core_OverflowBehavior::Allowed, TOverflowAllocator>;

//-------------------------------------------------------------------------------------------------
// Name	:	Core_FixedString
// Desc	:	Fixed-size string. If overflow is enabled, then the string is basically the same as Core_String
//-------------------------------------------------------------------------------------------------
template
<
	size_t TCount,
	Core_OverflowBehavior TOverflowBehavior = Core_OverflowBehavior::Allowed,
	typename TOverflowAllocator = EASTLAllocatorType
>
using Core_FixedString = Core_FixedBasicString<char, TCount, TOverflowBehavior, TOverflowAllocator>;

//-------------------------------------------------------------------------------------------------
// Name	:	Core_FixedWString
// Desc	:	Fixed-size wide-string. If overflow is enabled, then the string is basically the same as Core_String
//-------------------------------------------------------------------------------------------------
template
<
	size_t TCount,
	Core_OverflowBehavior TOverflowBehavior = Core_OverflowBehavior::Allowed,
	typename TOverflowAllocator = EASTLAllocatorType
>
using Core_FixedWString = Core_FixedBasicString<wchar_t, TCount, TOverflowBehavior, TOverflowAllocator>;
