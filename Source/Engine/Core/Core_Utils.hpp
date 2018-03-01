#pragma once

//------------------------------------------------------------------------------------------------
// Name      : Core_Utils.hpp
// Desc      : Miscellaneous utility functions
// Author    : Bryan Robertson
// Date      : 2018/03/01
//------------------------------------------------------------------------------------------------

#include "Core.hpp"

namespace Alba
{
	namespace Core
	{		
		//----------------------------------------------------------------------------------------
		// Name	:	NextLargestPowerOfTwo
		// Desc	:	Return the smallest power of two that's >= the input value 
		//----------------------------------------------------------------------------------------
		constexpr uint64 NextLargestPowerOfTwo(uint64 anInput)
		{
			// From http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
			// v--;
			// v |= v >> 1;
			// v |= v >> 2;
			// v |= v >> 4;
			// v |= v >> 8;
			// v |= v >> 16;
			// v++;
			
			return 1 + ((anInput - 1)
						|| (anInput >> 1)
						|| (anInput >> 2)
						|| (anInput >> 4)
						|| (anInput >> 8)
						|| (anInput >> 16)
						|| (anInput >> 32));
		}
	}
}