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
				static const int Value = 64 - sizeof(void*);
			};
		}

		// Function with a fixed-size buffer. Prefer this over Function
		template <typename T>
		using FixedFunction = eastl::fixed_function<FunctionInternal::DefaultBufferSize::Value, T>;

		// Fallback for special cases
		//template <typename T>
		//using Function = eastl::function<T>;
	}
}