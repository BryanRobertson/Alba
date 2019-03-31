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
			// v |= v >> 32;
			// v++;
			if (anInput == 0)
			{
				return 1;
			}

			uint64 result = anInput;

			--result;
			result |= result >> 1;
			result |= result >> 2;
			result |= result >> 4;
			result |= result >> 8;
			result |= result >> 16;
			result |= result >> 32;
			++result;

			return result;
		}

		constexpr uint32 NextLargestPowerOfTwo(uint32 anInput)
		{
			// From http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
			// v--;
			// v |= v >> 1;
			// v |= v >> 2;
			// v |= v >> 4;
			// v |= v >> 8;
			// v |= v >> 16;
			// v++;
			if (anInput == 0)
			{
				return 1;
			}

			uint32 result = anInput;

			--result;
			result |= result >> 1;
			result |= result >> 2;
			result |= result >> 4;
			result |= result >> 8;
			result |= result >> 16;
			++result;

			return result;
		}
	}
}