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
		enum HashOptions : uint8
		{ 
			CaseInsensitive, 
			CaseSensitive 
		};

		template <typename THashValueType>
		struct FNV1aTraits;

		template <>
		struct FNV1aTraits<uint32>
		{
			static constexpr uint32 ourOffsetBasis  = 0x811c9dc5;
			static constexpr uint32 ourPrime		= 0x1000193;
		};

		template <>
		struct FNV1aTraits<uint64>
		{
			static const uint64 ourOffsetBasis		= 0xcbf29ce484222325;
			static const uint64 ourPrime			= 0x100000001b3;
		};

		template <typename THashValueType, HashOptions THashOptions>
		struct FNV1aHashStatic
		{
			static constexpr THashValueType ourOffsetBasis  = FNV1aTraits<THashValueType>::ourOffsetBasis;
			static constexpr THashValueType ourPrime		= FNV1aTraits<THashValueType>::ourPrime;
			static constexpr THashValueType	ourInvalidHash	= ourOffsetBasis;

			static constexpr char ToLower(char c)
			{
				return c >= 'A' && c <= 'Z' 
					   ? c - ('A'-'a') 
					   : c;
			}

			static constexpr THashValueType Hash(StringView aString)
			{
				THashValueType hash = ourInvalidHash;
				for (size_t index = 0, count = aString.size(); index < count; ++index)
				{
					if constexpr (THashOptions == HashOptions::CaseSensitive)
					{
						hash = static_cast<THashValueType>((hash ^ aString[index]) * static_cast<unsigned long long>(ourPrime));
					}
					else
					{
						hash = static_cast<THashValueType>((hash ^ ToLower(aString[index])) * static_cast<unsigned long long>(ourPrime));
					}
				}

				return hash;
			}
		};

		template <HashOptions THashOptions>
		struct FNV1aHashStatic<uint16, THashOptions> : public FNV1aHashStatic<uint32, THashOptions>
		{
			static constexpr uint32 our16BitMask = (static_cast<uint32>(1 << 16) - 1); // 0xffff 

			static constexpr uint16 Hash(StringView aString)
			{
				const uint32 hash = FNV1aHashStatic<uint32, THashOptions>::Hash(aString);
				return static_cast<uint16>((hash >> 16) ^ (hash & our16BitMask));
			}

			static constexpr uint16 Convert(uint32 anInputHash)
			{
				return static_cast<uint16>((anInputHash >> 16) ^ (anInputHash & our16BitMask));
			}

			static constexpr uint16 ourInvalidHash = Convert(FNV1aHashStatic<uint32, THashOptions>::ourInvalidHash);
		};

		//-----------------------------------------------------------------------------------------
		// Name	:	Fnv1a16Hash
		// Desc	:	Hash a string using the FNV1a16 hashing algorithm
		//-----------------------------------------------------------------------------------------
		struct FNV1a16Hash : public FNV1aHashStatic<uint16, HashOptions::CaseSensitive> {};

		//-----------------------------------------------------------------------------------------
		// Name	:	Fnv1a16HashNoCase
		// Desc	:	Hash a string using the FNV1a16 hashing algorithm
		//			automatically converts the string to lower case first
		//-----------------------------------------------------------------------------------------
		struct FNV1a16HashNoCase : public FNV1aHashStatic<uint16, HashOptions::CaseInsensitive> {};

		//-----------------------------------------------------------------------------------------
		// Name	:	Fnv1a32Hash
		// Desc	:	Hash a string using the FNV1a32 hashing algorithm
		//-----------------------------------------------------------------------------------------
		struct FNV1a32Hash : public FNV1aHashStatic<uint32, HashOptions::CaseSensitive> {};	

		//-----------------------------------------------------------------------------------------
		// Name	:	Fnv1a32HashNoCase
		// Desc	:	Hash a string using the FNV1a32 hashing algorithm
		//			automatically converts the string to lower case first
		//-----------------------------------------------------------------------------------------
		struct FNV1a32HashNoCase : public FNV1aHashStatic<uint32, HashOptions::CaseInsensitive> {};

		//-----------------------------------------------------------------------------------------
		// Name	:	Fnv1a64Hash
		// Desc	:	Hash a string using the FNV1a64 hashing algorithm
		//-----------------------------------------------------------------------------------------
		struct FNV1a64Hash : public FNV1aHashStatic<uint64, HashOptions::CaseSensitive> {};
		
		//-----------------------------------------------------------------------------------------
		// Name	:	Fnv1a64HashNoCase
		// Desc	:	Hash a string using the FNV1a64 hashing algorithm
		//			automatically converts the string to lower case first
		//-----------------------------------------------------------------------------------------
		struct FNV1a64HashNoCase : public FNV1aHashStatic<uint64, HashOptions::CaseInsensitive> {};
	}
}