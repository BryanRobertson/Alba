//------------------------------------------------------------------------------------------------
// Name      : Core_Array.hpp
// Desc      : Static array wrapper type
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include <EASTL/array.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Core::Array<T, N>
		//------------------------------------------------------------------------------------------------
		template <typename TValueType, size_t N>
		using Array = eastl::array<TValueType, N>;
	}
}

