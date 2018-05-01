//------------------------------------------------------------------------------------------------
// Name      : Core_Hash.hpp
// Desc		 : Hashing algorithms
// Author    : Bryan Robertson
// Date      : 2018/02/27
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include "Core_BasicTypes.hpp"
#include "Core_StringView.hpp"
#include <cctype>

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
		struct FNV1a32Hash
		{
			static const uint32 ourInvalidHash = theFNV1a32OffsetBasis;

			static constexpr uint32 CompileTimeHash(const char* aString, uint32 aHashValue = theFNV1a32OffsetBasis)
			{
				return (aString && *aString != '\0')
					? CompileTimeHash(aString + 1, (aHashValue ^ *aString) * theFNV1a32Prime)
					: aHashValue;
			}

			static uint32 Hash(const StringView& aStringView)
			{
				uint32 hash = theFNV1a32OffsetBasis;
				for (char character : aStringView)
				{
					hash = (hash ^ character) * theFNV1a32Prime;
				}

				return hash;
			}
		};

		//-----------------------------------------------------------------------------------------
		// Name	:	Fnv1a32HashNoCase
		// Desc	:	Hash a string using the FNV1a32 hashing algorithm
		//			automatically converts the string to lower case first
		//-----------------------------------------------------------------------------------------
		struct FNV1a32HashNoCase
		{
			static const uint32 ourInvalidHash = theFNV1a32OffsetBasis;

			static constexpr uint32 CompileTimeHash(const char* aString, uint32 aHashValue = theFNV1a32OffsetBasis)
			{
				return (aString && *aString != '\0')
					? CompileTimeHash(aString + 1, (aHashValue ^ std::tolower(*aString)) * theFNV1a32Prime)
					: aHashValue;
			}

			static uint32 Hash(const StringView& aStringView)
			{
				uint32 hash = theFNV1a32OffsetBasis;
				for (char character : aStringView)
				{
					hash = (hash ^ std::tolower(character)) * theFNV1a32Prime;
				}

				return hash;
			}
		};

		//-----------------------------------------------------------------------------------------
		// Name	:	Fnv1a64Hash
		// Desc	:	Hash a string using the FNV1a64 hashing algorithm
		//-----------------------------------------------------------------------------------------
		struct FNV1a64Hash
		{
			static const uint64 ourInvalidHash = theFNV1a64OffsetBasis;

			static constexpr uint64 CompileTimeHash(const char* aString, uint64 aHashValue = theFNV1a64OffsetBasis)
			{
				return (aString && *aString != '\0')
					? CompileTimeHash(aString + 1, (aHashValue ^ *aString) * theFNV1a64Prime)
					: aHashValue;
			}

			static uint64 Hash(const StringView& aStringView)
			{
				uint64 hash = theFNV1a64OffsetBasis;
				for (char character : aStringView)
				{
					hash = (hash ^ character) * theFNV1a64Prime;
				}

				return hash;
			}
		};

		//-----------------------------------------------------------------------------------------
		// Name	:	Fnv1a64HashNoCase
		// Desc	:	Hash a string using the FNV1a64 hashing algorithm
		//			automatically converts the string to lower case first
		//-----------------------------------------------------------------------------------------
		struct FNV1a64HashNoCase
		{
			static const uint64 ourInvalidHash = theFNV1a64OffsetBasis;

			static constexpr uint64 CompileTimeHash(const char* aString, uint64 aHashValue = theFNV1a64OffsetBasis)
			{
				return (aString && *aString != '\0')
					? CompileTimeHash(aString + 1, (aHashValue ^ std::tolower(*aString)) * theFNV1a64Prime)
					: aHashValue;
			}

			static uint64 Hash(const StringView& aStringView)
			{
				uint64 hash = theFNV1a64OffsetBasis;
				for (char character : aStringView)
				{
					hash = (hash ^ std::tolower(character)) * theFNV1a64Prime;
				}

				return hash;
			}
		};
	}
}