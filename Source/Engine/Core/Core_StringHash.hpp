//------------------------------------------------------------------------------------------------
// Name      : Core_StringHash.hpp
// Desc		 : String hash type
// Author    : Bryan Robertson
// Date      : 2018/02/27
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include "Core_Hash.hpp"
#include "Core_Config.hpp"

namespace Alba
{
	namespace Core
	{
		struct FNVHashAlgorithm_Tag {};

		template <typename HashAlgorithm, typename THashValueType>
		struct TStringHashAlgorithm;

		template <>
		struct TStringHashAlgorithm<FNVHashAlgorithm_Tag, uint32>
		{
			static const uint32 ourInvalidHash = theFNV1a32OffsetBasis;
			
			static constexpr uint32 GetHash(const char* aString)
			{
				return FNV1a32Hash(aString);
			}
		};

		template <>
		struct TStringHashAlgorithm<FNVHashAlgorithm_Tag, uint64>
		{
			static const uint64 ourInvalidHash = theFNV1a64OffsetBasis;

			static constexpr uint64 GetHash(const char* aString)
			{
				return FNV1a64Hash(aString);
			}
		};

		//-----------------------------------------------------------------------------------------
		// Name	:	TStringHash
		// Desc	:	Template for a string hash. Uses Fnv1a hash as the hashing algorithm
		//-----------------------------------------------------------------------------------------
		template <typename THashValueType, typename THashAlgorithm=FNVHashAlgorithm_Tag>
		class TStringHash final
		{
			public:

				//=================================================================================
				// Public Types
				//=================================================================================
				typedef TStringHashAlgorithm<THashValueType, THashAlgorithm>		HashAlgorithm;
				
				//=================================================================================
				// Public Static Constants
				//=================================================================================
				static const THashValueType ourInvalidHashValue		= HashAlgorithm::ourInvalidHash;

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static constexpr TStringHash<THashValueType> FromString(const char* aString)
				{
					return HashAlgorithm::Hash(aString);
				}

				//=================================================================================
				// Public Constructors
				//=================================================================================
				TStringHash()
					: myHashValue(ourInvalidHashValue)
				{
				}

				explicit constexpr TStringHash(const char* aString)
					: myHashValue(HashAlgorithm::Hash(aString))
				{

				}

				explicit TStringHash(const String& aString)
					: myHashValue(HashAlgorithm::Hash(aString.c_str()))
				{

				}

				//=================================================================================
				// Public Methods
				//=================================================================================

			private:

				//=================================================================================
				// Private Static Data
				//=================================================================================
				#if defined(ALBA_DEBUG_STRINGHASH)
				struct DebugStringTable
				{
					//Mutex	myMutex;
				};
				#endif		

				//=================================================================================
				// Private Data
				//=================================================================================
				THashValueType	myHashValue;
		};
	}
}
