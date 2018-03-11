//-------------------------------------------------------------------------------------------------
// Name	:	Core_FixedVector.hpp
// Desc	:	Fixed-size vector
//-------------------------------------------------------------------------------------------------
#pragma once

#include "Core.hpp"
#include "Core_Container.hpp"
#include <EASTL/fixed_vector.h>

namespace Alba
{
	namespace Core
	{
		//-------------------------------------------------------------------------------------------------
		// Name	:	FixedVector
		// Desc	:	Fixed-size vector. If overflow is enabled, then the vector is basically the same as Core::Vector
		//-------------------------------------------------------------------------------------------------
		template 
		<
			typename TValueType,
			size_t TCount, 
			OverflowBehavior TOverflowBehavior=OverflowBehavior::Allowed,
			typename TOverflowAllocator = EASTLAllocatorType
		>
		using FixedVector = eastl::fixed_vector<TValueType, TCount, TOverflowBehavior==OverflowBehavior::Allowed, TOverflowAllocator>;
	}
}

