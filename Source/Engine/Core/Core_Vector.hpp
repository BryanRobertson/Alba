//------------------------------------------------------------------------------------------------
// Name      : Core_Vector.hpp
// Desc      : STL Vector equivalent
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include <EASTL/vector.h>
#include <EASTL/fixed_vector.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Core::Vector<T, Allocator>
		//------------------------------------------------------------------------------------------------
		template <typename TValueType, typename TAllocator = EASTLAllocatorType>
		using Vector = eastl::vector<TValueType, TAllocator>;

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

