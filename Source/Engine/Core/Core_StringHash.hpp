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
				// Public Static Methods
				//=================================================================================
				static constexpr TStringHashBase<THashValueType> FromString(const char* aString)
				{
					return HashAlgorithm::CompileTimeHash(aString);
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

				constexpr TStringHashBase(const char* aString, const CompileTimeHash&)
					: myHashValue(HashAlgorithm::CompileTimeHash(aString))
				{
					#if defined(ALBA_DEBUG_STRINGHASH)
					{
						myDebugString = ourDebugStringTable.Set(myHashValue, aString);
					}
					#endif
				}

				template <typename TCharType>
				explicit TStringHashBase(const BasicStringView<TCharType>& aStringView)
					: myHashValue(HashAlgorithm::Hash(aStringView.data()))
				{
					#if defined(ALBA_DEBUG_STRINGHASH)
					{
						myDebugString = ourDebugStringTable.Set(myHashValue, aStringView.data());
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
				bool operator == (const TStringHashBase<THashValueType, THashAlgorithm>& anOther) const
				{
					return myHashValue == anOther.myHashValue;
				}

				bool operator != (const TStringHashBase<THashValueType, THashAlgorithm>& anOther) const
				{
					return myHashValue != anOther.myHashValue;
				}

				bool operator <= (const TStringHashBase<THashValueType, THashAlgorithm>& anOther) const
				{
					return myHashValue <= anOther.myHashValue;
				}

				bool operator >= (const TStringHashBase<THashValueType, THashAlgorithm>& anOther) const
				{
					return myHashValue >= anOther.myHashValue;
				}

				bool operator < (const TStringHashBase<THashValueType, THashAlgorithm>& anOther) const
				{
					return myHashValue < anOther.myHashValue;
				}

				bool operator > (const TStringHashBase<THashValueType, THashAlgorithm>& anOther) const
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
			template <typename THashValueType, typename THashAlgorithm>
			typename TStringHashBase<THashValueType, THashAlgorithm>::DebugStringTable TStringHashBase<THashValueType, THashAlgorithm>::ourDebugStringTable;
		#endif

		//-----------------------------------------------------------------------------------------
		// Name	:	StringHash32
		// Desc	:	32-bit string hash
		//-----------------------------------------------------------------------------------------
		class ALBA_CORE_API StringHash32 : public TStringHashBase<uint32, FNV1a32Hash>
		{
			typedef TStringHashBase<uint32, FNV1a32Hash> Super;

			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				StringHash32();
				explicit StringHash32(uint32 aHash);

				template <typename TCharType, typename TAllocator>
					StringHash32(const BasicString<TCharType, TAllocator>& aString)
						: Super(BasicStringView<TCharType>(aString.c_str()))
				{

				}

				template<typename TCharType, size_t	TCount, OverflowBehavior TOverflowBehavior, typename TOverflowAllocator>
					StringHash32(const FixedBasicString<TCharType, TCount, TOverflowBehavior, TOverflowAllocator>& aString)
						: Super(BasicStringView<TCharType>(aString.c_str()))
				{
					
				}

				constexpr StringHash32(const char* aString)
					: Super(aString, CompileTimeHash())
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
		// Name	:	NoCaseStringHash32
		// Desc	:	32-bit string no-case hash (converts string to lower case before hashing)
		//-----------------------------------------------------------------------------------------
		class ALBA_CORE_API NoCaseStringHash32 : public TStringHashBase<uint32, FNV1a32HashNoCase>
		{
			typedef TStringHashBase<uint32, FNV1a32HashNoCase> Super;

			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				NoCaseStringHash32();
				explicit NoCaseStringHash32(uint32 aHash);

				template <typename TCharType, typename TAllocator>
					NoCaseStringHash32(const BasicString<TCharType, TAllocator>& aString)
						: Super(BasicStringView<TCharType>(aString.c_str()))
				{

				}

				template<typename TCharType, size_t	TCount, OverflowBehavior TOverflowBehavior, typename TOverflowAllocator>
					NoCaseStringHash32(const FixedBasicString<TCharType, TCount, TOverflowBehavior, TOverflowAllocator>& aString)
						: Super(BasicStringView<TCharType>(aString.c_str()))
				{

				}

				constexpr NoCaseStringHash32(const char* aString)
					: Super(aString, CompileTimeHash())
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
		class ALBA_CORE_API StringHash64 : public TStringHashBase<uint64, FNV1a64Hash>
		{
			typedef TStringHashBase<uint64, FNV1a64Hash> Super;

			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				StringHash64();
				explicit StringHash64(uint64 aHash);

				template <typename TCharType, typename TAllocator>
					StringHash64(const BasicString<TCharType, TAllocator>& aString)
						: Super(BasicStringView<TCharType>(aString.c_str()))
				{

				}

				template<typename TCharType, size_t	TCount, OverflowBehavior TOverflowBehavior, typename TOverflowAllocator>
					StringHash64(const FixedBasicString<TCharType, TCount, TOverflowBehavior, TOverflowAllocator>& aString)
						: Super(BasicStringView<TCharType>(aString.c_str()))
				{

				}

				constexpr StringHash64(const char* aString)
					: Super(aString, CompileTimeHash())
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
		class ALBA_CORE_API NoCaseStringHash64 : public TStringHashBase<uint64, FNV1a64HashNoCase>
		{
			typedef TStringHashBase<uint64, FNV1a64HashNoCase> Super;

			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				NoCaseStringHash64();
				explicit NoCaseStringHash64(uint64 aHash);

				template <typename TCharType, typename TAllocator>
				NoCaseStringHash64(const BasicString<TCharType, TAllocator>& aString)
					: Super(BasicStringView<TCharType>(aString.c_str(), aString.length()))
				{

				}

				template<typename TCharType, size_t	TCount, OverflowBehavior TOverflowBehavior, typename TOverflowAllocator>
				NoCaseStringHash64(const FixedBasicString<TCharType, TCount, TOverflowBehavior, TOverflowAllocator>& aString)
					: Super(BasicStringView<TCharType>(aString.c_str(), aString.length()))
				{

				}

				constexpr NoCaseStringHash64(const char* aString)
					: Super(aString, CompileTimeHash())
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
