//-------------------------------------------------------------------------------------------------
// Name      : BasicTypes.hpp
// Desc      : Basic types
// Author    : Bryan Robertson
// Date      : 20/02/2012
//-------------------------------------------------------------------------------------------------

#pragma once

#pragma warning( push, 3 )  
#include <cstdint>
#pragma warning( pop )  

namespace Core_BasicTypes
{
	//------------------------------------------------------------------------------------------------
	// Explicitly sized integers
	//------------------------------------------------------------------------------------------------
	typedef std::uint8_t			uint8;
	typedef std::int8_t				int8;

	typedef std::uint16_t			uint16;
	typedef std::int16_t			int16;

	typedef std::int32_t			int32;
	typedef std::uint32_t			uint32;

	typedef std::int64_t			int64;
	typedef std::uint64_t			uint64;

	//------------------------------------------------------------------------------------------------
	// Fastest integers for the requested size
	//------------------------------------------------------------------------------------------------
	typedef std::uint_fast8_t		fastuint8;
	typedef std::int_fast8_t		fastint8;

	typedef std::uint_fast16_t		fastuint16;
	typedef std::int_fast16_t		fastint16;

	typedef std::uint_fast32_t		fastint32;
	typedef std::int_fast32_t		fastuint32;

	typedef std::uint_fast64_t		fastint64;
	typedef std::int_fast64_t		fastuint64;

	//------------------------------------------------------------------------------------------------
	// Smallest integers for the requested size
	//------------------------------------------------------------------------------------------------
	typedef std::uint_least8_t		leastuint8;
	typedef std::int_least8_t		leastint8;

	typedef std::uint_least16_t		leastuint16;
	typedef std::int_least16_t		leastint16;

	typedef std::uint_least32_t		leastuint32;
	typedef std::int_least32_t		leastint32;

	typedef std::uint_least64_t		lastint64;
	typedef std::int_least64_t		lastuint64;

	//------------------------------------------------------------------------------------------------
	// Platform-defined integers
	//------------------------------------------------------------------------------------------------
	typedef unsigned int			uint;
}

using namespace Core_BasicTypes;