#pragma once

#include "Core.hpp"
#include "Core_TypeTraits.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name :	IsPowerOfTwo
		// Desc :	Return true if the passed in value is a power of two
		//-----------------------------------------------------------------------------------------
		template <typename TIntegerType, class=enable_if_t<is_integral_v<TIntegerType>> >
		constexpr bool IsPowerOfTwo(TIntegerType anInput)
		{
			return anInput && !(anInput & anInput - 1);
		}
	}
}