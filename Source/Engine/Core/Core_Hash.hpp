//------------------------------------------------------------------------------------------------
// Name      : Core_Hash.hpp
// Desc		 : Hashing algorithms
// Author    : Bryan Robertson
// Date      : 2018/02/27
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include "Core_BasicTypes.hpp"

namespace Alba
{
	namespace Core
	{
		static const uint32 theFNV1a32OffsetBasis	= 0x811c9dc5;
		static const uint32 theFNV1a32Prime			= 16777619;

		static const uint64 theFNV1a64OffsetBasis	= 0xcbf29ce484222325;
		static const uint64 theFNV1a64Prime			= 1099511628211;

		//-----------------------------------------------------------------------------------------
		// Name	:	Fnv1a32Hash
		// Desc	:	Hash a string using the FNV1a32 hashing algorithm
		//-----------------------------------------------------------------------------------------
		constexpr uint32 FNV1a32Hash(const char* aString, uint32 aHashValue = theFNV1a32OffsetBasis)
		{
			return (aString && *aString != '/0')
					? FNV1a32Hash(aString+1, (aHashValue ^ *aString) * theFNV1a32Prime)
					: aHashValue;
		}

		//-----------------------------------------------------------------------------------------
		// Name	:	FNV1a64Hash
		// Desc	:	Hash a string using the FNV1a64 hashing algorithm
		//-----------------------------------------------------------------------------------------
		constexpr uint64 FNV1a64Hash(const char* aString, uint64 aHashValue = theFNV1a64OffsetBasis)
		{
			return (aString && *aString != '/0')
					? FNV1a64Hash(aString+1, (aHashValue ^ *aString) * theFNV1a64Prime)
					: aHashValue;
		}
	}
}