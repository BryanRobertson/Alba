//-------------------------------------------------------------------------------------------------
// Name	:	Core_FixedVector.hpp
// Desc	:	Fixed-size vector
//-------------------------------------------------------------------------------------------------
#pragma once

#include "Core_API.hpp"
#include "Core_Container.hpp"
#include <EASTL/fixed_vector.h>

//-------------------------------------------------------------------------------------------------
// Name	:	Core_FixedVector
// Desc	:	Fixed-size vector. If overflow is enabled, then the string is basically the same as Core_Vector
//-------------------------------------------------------------------------------------------------
template 
<
	typename TValueType,
	size_t TCount, 
	Core_OverflowBehavior TOverflowBehavior=Core_OverflowBehavior::Allowed,
	typename TOverflowAllocator = EASTLAllocatorType
>
using Core_FixedVector = eastl::fixed_vector<TValueType, TCount, TOverflowBehavior== Core_OverflowBehavior::Allowed, TOverflowAllocator>;
