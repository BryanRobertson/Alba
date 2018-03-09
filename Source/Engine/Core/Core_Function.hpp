//------------------------------------------------------------------------------------------------
// Name      : Core_Function.hpp
// Desc      : STL Function equivalent
// Author    : Bryan Robertson
// Date      : 2018/03/01
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include <EASTL/functional.h>

namespace Alba
{
	namespace Core
	{
		template <typename... TArgs>
		using Function = eastl::function<TArgs...>;
	}
}