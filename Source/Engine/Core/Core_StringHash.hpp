//------------------------------------------------------------------------------------------------
// Name      : Core_StringHash.hpp
// Desc		 : String hash type
// Author    : Bryan Robertson
// Date      : 2018/02/27
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include "Core_Hash.hpp"
#include "Core_Mutex.hpp"
#include "Core_HashMap.hpp"
#include "Core_String.hpp"
#include "Core_FixedString.hpp"
#include "Core_Pair.hpp"

namespace Alba
{
	namespace Core
	{
		struct FNVHashAlgorithm_Tag {};
		struct FNVHashAlgorithmNoCase_Tag {};

		template <typename THashValueType, typename THashAlgorithmTag>
		struct TStringHashAlgorithm;

		template <>
		struct TStringHashAlgorithm<uint32, FNVHashAlgorithm_Tag>
		{
			static const uint32 ourInvalidHash = theFNV1a32OffsetBasis;
			
			static constexpr uint32 GetHash(const char* aString)
			{
				return FNV1a32Hash(aString);
			}
		};

		template <>
		struct TStringHashAlgorithm<uint64, FNVHashAlgorithm_Tag>
		{
			static const uint64 ourInvalidHash = theFNV1a64OffsetBasis;

			static constexpr uint64 GetHash(const char* aString)
			{
				return FNV1a64Hash(aString);
			}
		};

		template <>
		struct TStringHashAlgorithm<uint32, FNVHashAlgorithmNoCase_Tag>
		{
			static const uint32 ourInvalidHash = theFNV1a32OffsetBasis;

			static constexpr uint32 GetHash(const char* aString)
			{
				return FNV1a32HashNoCase(aString);
			}
		};

		template <>
		struct TStringHashAlgorithm<uint64, FNVHashAlgorithmNoCase_Tag>
		{
			static const uint64 ourInvalidHash = theFNV1a64OffsetBasis;

			static constexpr uint64 GetHash(const char* aString)
			{
				return FNV1a64HashNoCase(aString);
			}
		};

		//-----------------------------------------------------------------------------------------
		// Name	:	TStringHash
		// Desc	:	Template for a string hash. Uses Fnv1a hash as the hashing algorithm
		//-----------------------------------------------------------------------------------------
		template <typename THashValueType, typename THashAlgorithmTag=FNVHashAlgorithm_Tag>
		class TStringHashBase
		{
			public:

				//=================================================================================
				// Public Types
				//=================================================================================
				typedef TStringHashAlgorithm<THashValueType, THashAlgorithmTag>		HashAlgorithm;
				
				//=================================================================================
				// Public Static Constants
				//=================================================================================
				static const THashValueType ourInvalidHashValue		= HashAlgorithm::ourInvalidHash;

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static constexpr TStringHashBase<THashValueType> FromString(const char* aString)
				{
					return HashAlgorithm::GetHash(aString);
				}

				//=================================================================================
				// Public Constructors
				//=================================================================================
				TStringHashBase()
					: myHashValue(ourInvalidHashValue)
				{
					#if defined(ALBA_DEBUG_STRINGHASH)
						myDebugString = nullptr;
					#endif
				}

				explicit constexpr TStringHashBase(const char* aString)
					: myHashValue(HashAlgorithm::GetHash(aString))
				{
					#if defined(ALBA_DEBUG_STRINGHASH)
					{
						myDebugString = ourDebugStringTable.Set(myHashValue, aString);
					}
					#endif
				}

				template <typename TCharType, typename TAllocator>
				explicit TStringHashBase(const BasicString<TCharType, TAllocator>& aString)
					: myHashValue(HashAlgorithm::GetHash(aString.c_str()))
				{
					#if defined(ALBA_DEBUG_STRINGHASH)
					{
						myDebugString = ourDebugStringTable.Set(myHashValue, aString.c_str());
					}
					#endif
				}

				explicit TStringHashBase(THashValueType aHash)
					: myHashValue(aHash)
				{
					#if defined(ALBA_DEBUG_STRINGHASH)
					{
						myDebugString = ourDebugStringTable.Get(myHashValue);
					}
					#endif
				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				THashValueType GetHash() const		
				{
					return myHashValue; 
				}

				bool IsValid() const
				{ 
					return myHashValue != ourInvalidHashValue;
				}

				//---------------------------------------------------------------------------------
				// Operator overloads
				//---------------------------------------------------------------------------------
				bool operator == (const TStringHashBase<THashValueType, THashAlgorithmTag>& anOther) const
				{
					return myHashValue == anOther.myHashValue;
				}

				bool operator != (const TStringHashBase<THashValueType, THashAlgorithmTag>& anOther) const
				{
					return myHashValue != anOther.myHashValue;
				}

				bool operator <= (const TStringHashBase<THashValueType, THashAlgorithmTag>& anOther) const
				{
					return myHashValue <= anOther.myHashValue;
				}

				bool operator >= (const TStringHashBase<THashValueType, THashAlgorithmTag>& anOther) const
				{
					return myHashValue >= anOther.myHashValue;
				}

				bool operator < (const TStringHashBase<THashValueType, THashAlgorithmTag>& anOther) const
				{
					return myHashValue < anOther.myHashValue;
				}

				bool operator > (const TStringHashBase<THashValueType, THashAlgorithmTag>& anOther) const
				{
					return myHashValue > anOther.myHashValue;
				}
				//---------------------------------------------------------------------------------

				#if defined(ALBA_DEBUG_STRINGHASH)
					const char* Debug_GetString() const 
					{ 
						return ourDebugStringTable.Get(myHashValue); 
					}
				#endif

			private:

				//=================================================================================
				// Private Static Data
				//=================================================================================
				#if defined(ALBA_DEBUG_STRINGHASH)
				struct DebugStringTable 
				{
					//-----------------------------------------------------------------------------
					// Set entry in debug string table
					//-----------------------------------------------------------------------------
					const char* Set(THashValueType aHash, const char* aString)
					{
						const char* debugStr = nullptr;

						FixedString<256> fixedStr(aString);
						ScopedWriterMutexLock lock(myDictionaryMutex);

						auto itr = myDebugStringTable.find(aHash);
						if (itr == myDebugStringTable.end())
						{
							Pair<THashValueType, String> pair(aHash, String(fixedStr.c_str()));
							debugStr = pair.second.c_str();

							myDebugStringTable.insert(std::move(pair));
						}
						else
						{
							const String& str = itr->second;
							debugStr = str.c_str();

							ALBA_ASSERT
							(
								str.compare(fixedStr.c_str()) == 0 || str.comparei(fixedStr.c_str()) == 0, ""
							);
						}

						return debugStr;
					}

					//-----------------------------------------------------------------------------
					// Get entry in debug string table
					//-----------------------------------------------------------------------------
					const char* Get(THashValueType aHash)
					{
						if (aHash == ourInvalidHashValue)
						{
							return "";
						}

						ScopedReaderMutexLock lock(myDictionaryMutex);

						auto itr = myDebugStringTable.find(aHash);
						return itr != myDebugStringTable.end() ? itr->second.c_str() : "<NOT FOUND>";
					}

					HashMap<THashValueType, String>	myDebugStringTable;
					ReadWriteMutex					myDictionaryMutex;
				};

				static DebugStringTable ourDebugStringTable;
				#endif

				//=================================================================================
				// Private Data
				//=================================================================================
				THashValueType	myHashValue;

				#if defined(ALBA_DEBUG_STRINGHASH)
					const char* myDebugString;
				#endif	
		};

		#if defined(ALBA_DEBUG_STRINGHASH)
			template <typename THashValueType, typename THashAlgorithmTag>
			typename TStringHashBase<THashValueType, THashAlgorithmTag>::DebugStringTable TStringHashBase<THashValueType, THashAlgorithmTag>::ourDebugStringTable;
		#endif

		//-----------------------------------------------------------------------------------------
		// Name	:	StringHash32
		// Desc	:	32-bit string hash
		//-----------------------------------------------------------------------------------------
		class ALBA_CORE_API StringHash32 : public TStringHashBase<uint32>
		{
			typedef TStringHashBase<uint32> Super;

			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				StringHash32();
				explicit StringHash32(uint32 aHash);

				template <typename TCharType, typename TAllocator>
				explicit StringHash32(const BasicString<TCharType, TAllocator>& aString)
					: Super(aString)
				{

				}

				explicit constexpr StringHash32(const char* aString)
					: Super(aString)
				{

				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				FixedString<64> LogString()
				{
					#if defined(ALBA_DEBUG_STRINGHASH)
						return Debug_GetString();
					#else
						return FormatString<64>("0x%x", GetHash());
					#endif
				}
		};

		//-----------------------------------------------------------------------------------------
		// Name	:	StringHash64
		// Desc	:	64-bit string hash
		//-----------------------------------------------------------------------------------------
		class ALBA_CORE_API StringHash64 : public TStringHashBase<uint64>
		{
			typedef TStringHashBase<uint64> Super;

			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				StringHash64();
				explicit StringHash64(uint64 aHash);

				template <typename TCharType, typename TAllocator>
				explicit StringHash64(const BasicString<TCharType, TAllocator>& aString)
					: Super(aString)
				{

				}

				explicit constexpr StringHash64(const char* aString)
					: Super(aString)
				{

				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				FixedString<64> LogString()
				{
					#if defined(ALBA_DEBUG_STRINGHASH)
						return Debug_GetString();
					#else
						return FormatString<32>("0x%x", GetHash());
					#endif
				}
		};

		//-----------------------------------------------------------------------------------------
		// Name	:	NoCaseStringHash32
		// Desc	:	32-bit string no-case hash (converts string to lower case before hashing)
		//-----------------------------------------------------------------------------------------
		class ALBA_CORE_API NoCaseStringHash32 : public TStringHashBase<uint32, FNVHashAlgorithmNoCase_Tag>
		{
			typedef TStringHashBase<uint32, FNVHashAlgorithmNoCase_Tag> Super;

			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				NoCaseStringHash32();
				explicit NoCaseStringHash32(uint32 aHash);

				template <typename TCharType, typename TAllocator>
				explicit NoCaseStringHash32(const BasicString<TCharType, TAllocator>& aString)
					: Super(aString)
				{

				}

				explicit constexpr NoCaseStringHash32(const char* aString)
					: Super(aString)
				{

				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				FixedString<64> LogString()
				{
					#if defined(ALBA_DEBUG_STRINGHASH)
						return Debug_GetString();
					#else
						return FormatString<64>("0x%x", GetHash());
					#endif
				}
		};

		//-----------------------------------------------------------------------------------------
		// Name	:	NoCaseStringHash64
		// Desc	:	64-bit string no-case hash (converts string to lower case before hashing)
		//-----------------------------------------------------------------------------------------
		class ALBA_CORE_API NoCaseStringHash64 : public TStringHashBase<uint64, FNVHashAlgorithmNoCase_Tag>
		{
			typedef TStringHashBase<uint64, FNVHashAlgorithmNoCase_Tag> Super;

			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				NoCaseStringHash64();
				explicit NoCaseStringHash64(uint64 aHash);

				template <typename TCharType, typename TAllocator>
				explicit NoCaseStringHash64(const BasicString<TCharType, TAllocator>& aString)
					: Super(aString)
				{

				}

				explicit constexpr NoCaseStringHash64(const char* aString)
					: Super(aString)
				{

				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				FixedString<64> LogString()
				{
					#if defined(ALBA_DEBUG_STRINGHASH)
						return Debug_GetString();
					#else
						return FormatString<64>("0x%x", GetHash());
					#endif
				}
		};
	}
}

template <> struct eastl::hash<Alba::Core::StringHash32>
{
	size_t operator()(Alba::Core::StringHash32 val) const { return static_cast<size_t>(val.GetHash()); }
};

template <> struct eastl::hash<Alba::Core::StringHash64>
{
	size_t operator()(Alba::Core::StringHash64 val) const { return static_cast<size_t>(val.GetHash()); }
};

template <> struct eastl::hash<Alba::Core::NoCaseStringHash32>
{
	size_t operator()(Alba::Core::NoCaseStringHash32 val) const { return static_cast<size_t>(val.GetHash()); }
};

template <> struct eastl::hash<Alba::Core::NoCaseStringHash64>
{
	size_t operator()(Alba::Core::NoCaseStringHash64 val) const { return static_cast<size_t>(val.GetHash()); }
};

template <> struct std::hash<Alba::Core::StringHash32>
{
	size_t operator()(Alba::Core::StringHash32 val) const { return static_cast<size_t>(val.GetHash()); }
};

template <> struct std::hash<Alba::Core::StringHash64>
{
	size_t operator()(Alba::Core::StringHash64 val) const { return static_cast<size_t>(val.GetHash()); }
};

template <> struct std::hash<Alba::Core::NoCaseStringHash32>
{
	size_t operator()(Alba::Core::NoCaseStringHash32 val) const { return static_cast<size_t>(val.GetHash()); }
};

template <> struct std::hash<Alba::Core::NoCaseStringHash64>
{
	size_t operator()(Alba::Core::NoCaseStringHash64 val) const { return static_cast<size_t>(val.GetHash()); }
};
