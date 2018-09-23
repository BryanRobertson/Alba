//------------------------------------------------------------------------------------------------
// Name      : Core_Function.hpp
// Desc      : STL Function equivalent
// Author    : Bryan Robertson
// Date      : 2018/03/01
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include "Core_AlignedStorage.hpp"
#include "Core_Platform.hpp"
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
				static const int Value = Core::HardwareConstants::theL1CacheLineSize - sizeof(void*);
			};
		}

		// Function with a fixed-size buffer. Prefer this over Function
		template <typename T, size_t TSize=FunctionInternal::DefaultBufferSize::Value>
		using FixedFunction = eastl::fixed_function<TSize, T>;
	}
}