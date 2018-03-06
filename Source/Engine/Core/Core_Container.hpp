//------------------------------------------------------------------------------------------------
// Name      : Core_Deque.hpp
// Desc      : STL Deque equivalent
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include "Core_BasicTypes.hpp"

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Overflow behavior
		//------------------------------------------------------------------------------------------------
		enum class OverflowBehavior : uint8
		{
			NotAllowed = 0,
			Allowed = 1
		};
	}
}

