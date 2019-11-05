//-------------------------------------------------------------------------------------------------
// Name      : BasicTypes.hpp
// Desc      : Basic types
// Author    : Bryan Robertson
// Date      : 20/02/2012
//-------------------------------------------------------------------------------------------------

#pragma once

#pragma warning( push, 3 )  
#include <cstdint>
#include <cstddef>
#pragma warning( pop )  

namespace Alba
{ 
	inline namespace BasicTypes
	{
		using byte		= std::byte;

		//------------------------------------------------------------------------------------------------
		// Explicitly sized integers
		//------------------------------------------------------------------------------------------------
		using uint8		= std::uint8_t;
		using int8		= std::int8_t;
		
		using uint16	= std::uint16_t;
		using int16		= std::int16_t;

		using uint32	= std::uint32_t;
		using int32		= std::int32_t;

		using uint64	= std::uint64_t;
		using int64		= std::int64_t;

		//------------------------------------------------------------------------------------------------
		// Most efficient types that are at least some specified size
		//------------------------------------------------------------------------------------------------
		using uint8fast	 = std::uint_fast8_t;
		using int8fast	 = std::int_fast8_t;
		
		using uint16fast = std::uint_fast16_t;
		using int16fast	 = std::int_fast16_t;

		using uint32fast = std::uint_fast32_t;
		using int32fast  = std::int_fast32_t;

		using uint64fast = std::uint_fast64_t;
		using int64fast	 = std::int_fast64_t;

		//------------------------------------------------------------------------------------------------
		// Smallest types that can hold at least specified size
		//------------------------------------------------------------------------------------------------
		using uint8least  = std::uint_least8_t;
		using int8least   = std::int_least8_t;

		using uint16least = std::uint_least16_t;
		using int16least  = std::int_least16_t;

		using uint32least = std::uint_least32_t;
		using int32least  = std::int_least32_t;

		using uint64least = std::uint_least64_t;
		using int64least  = std::int_least64_t;

		//------------------------------------------------------------------------------------------------
		// Platform-defined integers
		//------------------------------------------------------------------------------------------------
		using uint		= unsigned int;

		//------------------------------------------------------------------------------------------------
		// Characters
		//------------------------------------------------------------------------------------------------
		using char8_t	= char;
		using uchar8_t	= unsigned char;
	}
}

