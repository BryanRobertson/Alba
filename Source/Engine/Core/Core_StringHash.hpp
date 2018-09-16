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
#include "Core_StringView.hpp"
#include "Core_FixedString.hpp"
#include "Core_StringUtils.hpp"
#include "Core_Pair.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	TStringHash
		// Desc	:	Template for a string hash. Uses Fnv1a hash as the hashing algorithm
		//-----------------------------------------------------------------------------------------
		template <typename THashValueType, typename THashAlgorithm=FNV1a32Hash>
		class TStringHashBase
		{
			public:

				//=================================================================================
				// Public Types
				//=================================================================================
				typedef THashValueType	HashValueType;
				typedef THashAlgorithm	HashAlgorithm;

				struct CompileTimeHash{};
				
				//=================================================================================
				// Public Static Constants
				//=================================================================================
				static const THashValueType ourInvalidHashValue		= HashAlgorithm::ourInvalidHash;

				//=================================================================================
				// Public Constructors
				//=================================================================================
				constexpr TStringHashBase()
					: myHashValue(ourInvalidHashValue)
				{
					#if defined(ALBA_DEBUG_STRINGHASH)
						myDebugString = nullptr;
					#endif
				}

				explicit TStringHashBase(StringView aStringView)
					: myHashValue(HashAlgorithm::Hash(aStringView))
				{
					#if defined(ALBA_DEBUG_STRINGHASH)
					{
						myDebugString = ourDebugStringTable.Set(myHashValue, aStringView);
					}
					#endif
				}

				struct CompileTimeHash
				{
					constexpr CompileTimeHash() {}
				};

				explicit constexpr TStringHashBase(StringView aStringView, const CompileTimeHash&)
					: myHashValue(HashAlgorithm::Hash(aStringView))
				{
					#if defined(ALBA_DEBUG_STRINGHASH)
					{
						myDebugString = aStringView.data();
					}
					#endif
				}

				explicit constexpr TStringHashBase(THashValueType aHash)
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
				constexpr THashValueType GetHash() const
				{
					return myHashValue; 
				}

				constexpr bool IsValid() const
				{ 
					return myHashValue != ourInvalidHashValue;
				}

				//---------------------------------------------------------------------------------
				// Operator overloads
				//---------------------------------------------------------------------------------
				constexpr bool operator == (const TStringHashBase<THashValueType, THashAlgorithm>& anOther) const
				{
					return myHashValue == anOther.myHashValue;
				}

				constexpr bool operator != (const TStringHashBase<THashValueType, THashAlgorithm>& anOther) const
				{
					return myHashValue != anOther.myHashValue;
				}

				constexpr bool operator <= (const TStringHashBase<THashValueType, THashAlgorithm>& anOther) const
				{
					return myHashValue <= anOther.myHashValue;
				}

				constexpr bool operator >= (const TStringHashBase<THashValueType, THashAlgorithm>& anOther) const
				{
					return myHashValue >= anOther.myHashValue;
				}

				constexpr bool operator < (const TStringHashBase<THashValueType, THashAlgorithm>& anOther) const
				{
					return myHashValue < anOther.myHashValue;
				}

				constexpr bool operator > (const TStringHashBase<THashValueType, THashAlgorithm>& anOther) const
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

				// LogString is defined even when string hashing debug isn't enabled. In that case it just converts the hash to a string
				constexpr FixedString<64> LogString()
				{
					#if defined(ALBA_DEBUG_STRINGHASH)
						if (myDebugString)
						{
							return myDebugString;
						}
						else
						{
							myDebugString = Debug_GetString();
						}

						return myDebugString;
					#else
						return FormatString<64>("0x%x", GetHash());
					#endif
				}

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
					const char* Set(THashValueType aHash, StringView aString)
					{
						const char* debugStr = nullptr;

						FixedString<256> fixedStr(aString.begin(), aString.end());

						{
							ScopedWriterMutexLock lock(myDictionaryMutex);

							auto itr = myDebugStringTable.find(aHash);
							if (itr == myDebugStringTable.end())
							{
								myDebugStringTable.emplace(aHash, String(fixedStr.begin(), fixedStr.end()));
								debugStr = myDebugStringTable[aHash].c_str();
							}
							else
							{
								const String& str = itr->second;
								debugStr = str.c_str();

								ALBA_ASSERT
								(
									str.compare(fixedStr.c_str()) == 0 || str.comparei(fixedStr.c_str()) == 0,
									"Hash collision - %s has the same hash as %s",
									aString, str.c_str()
								);
							}
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
			template <typename THashValueType, typename THashAlgorithm>
			typename TStringHashBase<THashValueType, THashAlgorithm>::DebugStringTable TStringHashBase<THashValueType, THashAlgorithm>::ourDebugStringTable;
		#endif

		typedef TStringHashBase<uint32, FNV1a32Hash>		StringHash32;
		typedef TStringHashBase<uint32, FNV1a32HashNoCase>	NoCaseStringHash32;
		typedef TStringHashBase<uint64, FNV1a64Hash>		StringHash64;
		typedef TStringHashBase<uint64, FNV1a64HashNoCase>	NoCaseStringHash64;
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

namespace Alba
{
	namespace StringHashLiterals
	{
		inline constexpr Alba::Core::StringHash32 operator "" _hash32(const char* aStr, size_t aSize)
		{
			return Alba::Core::StringHash32(Alba::Core::StringView(aStr, aSize), Alba::Core::StringHash32::CompileTimeHash());
		}

		inline constexpr Alba::Core::StringHash64 operator "" _hash64(const char* aStr, size_t aSize)
		{
			return Alba::Core::StringHash64(Alba::Core::StringView(aStr, aSize), Alba::Core::StringHash64::CompileTimeHash());
		}

		inline constexpr Alba::Core::NoCaseStringHash32 operator "" _nocasehash32(const char* aStr, size_t aSize)
		{
			return Alba::Core::NoCaseStringHash32(Alba::Core::StringView(aStr, aSize), Alba::Core::NoCaseStringHash32::CompileTimeHash());
		}

		inline constexpr Alba::Core::NoCaseStringHash64 operator "" _nocasehash64(const char* aStr, size_t aSize)
		{
			return Alba::Core::NoCaseStringHash64(Alba::Core::StringView(aStr, aSize), Alba::Core::NoCaseStringHash64::CompileTimeHash());
		}
	}
}
