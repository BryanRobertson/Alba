//------------------------------------------------------------------------------------------------
// Name      : Core_Function.hpp
// Desc      : STL Function equivalent
// Author    : Bryan Robertson
// Date      : 2018/03/01
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include "Core_AlignedStorage.hpp"
#include <EASTL/fixed_function.h>
//#include <functional>

namespace Alba
{
	namespace Core
	{
		namespace FunctionInternal
		{
			struct DefaultBufferSize
			{
				static const int Value = 32;
			};
		}

		template <typename T>
		using Function = eastl::fixed_function<FunctionInternal::DefaultBufferSize::Value, T>;
	}
}