//------------------------------------------------------------------------------------------------
// Name      : StringHash.hpp
// Desc      : String hashing
// Author    : Bryan Robertson
// Date      : 20/02/2012
//------------------------------------------------------------------------------------------------

#pragma once

#include <cstring>
#include <string>

#include "Core_Config.hpp"
#include "Core_API.hpp"
#include "Core_BasicTypes.hpp"
#include "Core_FNV1aHash.hpp"
#include "Core_String.hpp"
#include "Core_FixedString.hpp"
#include "Core_StringFormatUtils.hpp"

//-------------------------------------------------------------------------------------------------
// Name : ALBA_STATIC_HASH
// Desc : Return compile-time hash for string literal
//-------------------------------------------------------------------------------------------------
#define ALBA_STATIC_HASH(str)	::Core_StringHash64::StaticHash(str)

//=================================================================================================
// Name : Core_TStringHash
// Desc : Class encapsulating a string hash. 
//		  The default StringHash type is typedefed as StringHash below
//=================================================================================================
template <typename TCharType, typename TAlgorithm>
class Core_TStringHash
{
	public:

		//=================================================================================================
		// Public Types 
		//=================================================================================================
		typedef typename TAlgorithm::HashType											HashCode;
		typedef Core_TStringHash<TCharType, TAlgorithm>									StringHashType;

		typedef Core_FixedBasicString<TCharType, 16, Core_OverflowBehavior::Allowed>	DebugStringType;

		//=================================================================================================
		// Public Constants
		//=================================================================================================
		static const HashCode	InvalidHash = 0;

		//=================================================================================================
		// Public Constructors
		//=================================================================================================

		//-------------------------------------------------------------------------------------------------
		// Name : Constructor
		// Desc : Default constructor
		//-------------------------------------------------------------------------------------------------
		Core_TStringHash()
			: myHashCode(InvalidHash)
		{
		}

		//-------------------------------------------------------------------------------------------------
		// Name : Constructor
		// Desc : Return hash for a c-style string
		//-------------------------------------------------------------------------------------------------
		explicit Core_TStringHash(const TCharType* str)
			#ifdef ALBA_DEBUG_STRINGHASH
				: m_debugString(str)
			#endif
		{
			HashCode hash = TAlgorithm::Initialise();
			myHashCode = TAlgorithm::ProcessCharacterSequence(hash, str, str + ::std::strlen(str));
		}

		//-------------------------------------------------------------------------------------------------
		// Name : Constructor
		// Desc : Return hash for a c-style string
		//-------------------------------------------------------------------------------------------------
		explicit Core_TStringHash(const TCharType* str, const size_t length)
			#ifdef ALBA_DEBUG_STRINGHASH
						: m_debugString(str)
			#endif
		{
			HashCode hash = TAlgorithm::Initialise();
			myHashCode = TAlgorithm::ProcessCharacterSequence(hash, str, str + length);
		}

		//-------------------------------------------------------------------------------------------------
		// Name : Constructor
		// Desc : Return hash for a c++ string
		//-------------------------------------------------------------------------------------------------
		template <typename TCharTraits, typename TAllocatorType>
		explicit Core_TStringHash(const std::basic_string<TCharType, TCharTraits, TAllocatorType>& str)
			#ifdef ALBA_DEBUG_STRINGHASH
				: m_debugString(str)
			#endif
		{
			HashCode hash = TAlgorithm::Initialise();
			myHashCode = TAlgorithm::ProcessCharacterSequence(hash, str.cbegin(), str.cend());
		}

		//-------------------------------------------------------------------------------------------------
		// Name : Constructor
		// Desc : Return hash for an EASTL string
		//-------------------------------------------------------------------------------------------------
		template <typename TAllocatorType>
		explicit Core_TStringHash(const eastl::basic_string<TCharType, TAllocatorType>& str)
			#ifdef ALBA_DEBUG_STRINGHASH
				: m_debugString(str)
			#endif
		{
			HashCode hash = TAlgorithm::Initialise();
			myHashCode = TAlgorithm::ProcessCharacterSequence(hash, str.cbegin(), str.cend());
		}

		//-------------------------------------------------------------------------------------------------
		// Name : StaticHash
		// Desc : Return hash for a static string
		//-------------------------------------------------------------------------------------------------
		template<size_t TLength>
		static Core_TStringHash<TCharType, TAlgorithm> StaticHash(const TCharType (&stringLiteral)[TLength])
		{
			const HashCode hashCode = TAlgorithm::HashStaticString<TLength>(stringLiteral);

			#ifdef ALBA_DEBUG_STRINGHASH
				const TCharType* debugString = &stringLiteral[0];
				return Core_TStringHash<TCharType, TAlgorithm>(hashCode, debugString);
			#else
				return Core_TStringHash<TCharType, TAlgorithm>(hashCode);
			#endif
		}

		//=================================================================================================
		// Public Methods 
		//=================================================================================================

		//-------------------------------------------------------------------------------------------------
		// Name : GetValue
		// Desc : Get the underlying value of the hash code
		//-------------------------------------------------------------------------------------------------
		HashCode GetValue() const
		{
			return myHashCode;
		}

		//=================================================================================================
		// Public Operators 
		//=================================================================================================
				
		//-------------------------------------------------------------------------------------------------
		// Name : operator==
		//-------------------------------------------------------------------------------------------------
		bool operator == (HashCode value) const
		{
			return myHashCode == value;
		}

		//-------------------------------------------------------------------------------------------------
		// Name : operator<
		//-------------------------------------------------------------------------------------------------
		bool operator< (const StringHashType& rhs) const
		{
			return myHashCode < rhs.myHashCode;
		}

		//-------------------------------------------------------------------------------------------------
		// Name : operator<=
		//-------------------------------------------------------------------------------------------------
		bool operator<= (const StringHashType& rhs) const
		{
			return myHashCode <= rhs.myHashCode;
		}

		//-------------------------------------------------------------------------------------------------
		// Name : operator>
		//-------------------------------------------------------------------------------------------------
		bool operator> (const StringHashType& rhs) const
		{
			return myHashCode > rhs.myHashCode;
		}

		//-------------------------------------------------------------------------------------------------
		// Name : operator>=
		//-------------------------------------------------------------------------------------------------
		bool operator>= (const StringHashType& rhs) const
		{
			return myHashCode >= rhs.myHashCode;
		}

		//-------------------------------------------------------------------------------------------------
		// Name	:	ToString
		// Desc	:	Returns a string representing the hash... if string debugging is enabled then
		//			this will be the string that was used to generate the hash,
		//			otherwise it will be a string representation of the hash value
		//-------------------------------------------------------------------------------------------------
		DebugStringType	ToHexString() const
		{
			return Core_StringFormatter<DebugStringType>::ToHexString(myHashCode);
		}

		#ifdef ALBA_DEBUG_STRINGHASH
			const DebugStringType& ToString() const
			{
				return m_debugString;
			}
		#else
			DebugStringType	ToString() const
			{
				return ToHexString();
			}
		#endif

	private:

		//=================================================================================================
		// Private Constructors
		//=================================================================================================
		#ifdef ALBA_DEBUG_STRINGHASH
			Core_TStringHash(HashCode hashCode, const char* debugString)
				: myHashCode(hashCode)
				, m_debugString(debugString)
			{
			}
		#else
			Core_TStringHash(HashCode hashCode
				: myHashCode(hashCode)
			{
			}
		#endif

		//=================================================================================================
		// Private Data 
		//=================================================================================================
		HashCode	myHashCode;

		#ifdef ALBA_DEBUG_STRINGHASH
			DebugStringType	m_debugString;
		#endif
};


//=================================================================================================
// Typedefs
//=================================================================================================
typedef		Core_TStringHash<char, TFNV1aHash<uint32> >			Core_StringHash32;
typedef		Core_TStringHash<wchar_t, TFNV1aHash<uint32> >		Core_WStringHash32;

typedef		Core_TStringHash<char, TFNV1aHash<uint64> >			Core_StringHash64;
typedef		Core_TStringHash<wchar_t, TFNV1aHash<uint64> >		Core_WStringHash64;

//=================================================================================================
// C++11 literals
//=================================================================================================
namespace Core_StringHashLiterals
{
	//------------------------------------------------------------------------------------------------
	// Name	:	hash32
	// Desc	:	Create a 32 bit string hash from a string literal
	//------------------------------------------------------------------------------------------------
	auto operator "" _hash32(const char* str, size_t length)
	{
		return ::Core_TStringHash<char, TFNV1aHash<uint32> >(str, length);
	}

	auto operator "" _hash32(const wchar_t* str, size_t length)
	{
		return ::Core_TStringHash<wchar_t, TFNV1aHash<uint32> >(str, length);
	}

	auto operator "" _hash32(const char16_t* str, size_t length)
	{
		return ::Core_TStringHash<char16_t, TFNV1aHash<uint32> >(str, length);
	}

	auto operator "" _hash32(const char32_t* str, size_t length)
	{
		return ::Core_TStringHash<char32_t, TFNV1aHash<uint32> >(str, length);
	}

	//------------------------------------------------------------------------------------------------
	// Name	:	hash64
	// Desc	:	Create a 64 bit string hash from a string literal
	//------------------------------------------------------------------------------------------------
	auto operator "" _hash64(const char* str, size_t length)
	{
		return ::Core_TStringHash<char, TFNV1aHash<uint64> >(str, length);
	}

	auto operator "" _hash64(const wchar_t* str, size_t length)
	{
		return ::Core_TStringHash<wchar_t, TFNV1aHash<uint64> >(str, length);
	}

	auto operator "" _hash64(const char16_t* str, size_t length)
	{
		return ::Core_TStringHash<char16_t, TFNV1aHash<uint64> >(str, length);
	}

	auto operator "" _hash64(const char32_t* str, size_t length)
	{
		return ::Core_TStringHash<char32_t, TFNV1aHash<uint64> >(str, length);
	}

	//------------------------------------------------------------------------------------------------
	// Name	:	hash
	// Desc	:	Create a hash from a string literal using the default hash size
	//------------------------------------------------------------------------------------------------
	auto operator "" _hash(const char* str, size_t length)
	{
		return ::Core_TStringHash<char, TFNV1aHash<uint64> >(str, length);
	}

	auto operator "" _hash(const wchar_t* str, size_t length)
	{
		return ::Core_TStringHash<wchar_t, TFNV1aHash<uint64> >(str, length);
	}

	auto operator "" _hash(const char16_t* str, size_t length)
	{
		return ::Core_TStringHash<char16_t, TFNV1aHash<uint64> >(str, length);
	}

	auto operator "" _hash(const char32_t* str, size_t length)
	{
		return ::Core_TStringHash<char32_t, TFNV1aHash<uint64> >(str, length);
	}

	//------------------------------------------------------------------------------------------------
	// Name	:	fnv1a32
	// Desc	:	Create a 32 bit string FNV1ahash from a string literal
	//			Specifies the hashing algorithm
	//------------------------------------------------------------------------------------------------
	auto operator "" _fnv1a32(const char* str, size_t length)
	{
		return ::Core_TStringHash<char, TFNV1aHash<uint32> >(str, length);
	}

	auto operator "" _fnv1a32(const wchar_t* str, size_t length)
	{
		return ::Core_TStringHash<wchar_t, TFNV1aHash<uint32> >(str, length);
	}

	auto operator "" _fnv1a32(const char16_t* str, size_t length)
	{
		return ::Core_TStringHash<char16_t, TFNV1aHash<uint32> >(str, length);
	}

	auto operator "" _fnv1a32(const char32_t* str, size_t length)
	{
		return ::Core_TStringHash<char32_t, TFNV1aHash<uint32> >(str, length);
	}

	//------------------------------------------------------------------------------------------------
	// Name	:	fnv1a64
	// Desc	:	Create a 64 bit string FNV1ahash from a string literal
	//			Specifies the hashing algorithm
	//------------------------------------------------------------------------------------------------
	auto operator "" _fnv1a64(const char* str, size_t length)
	{
		return ::Core_TStringHash<char, TFNV1aHash<uint64> >(str, length);
	}

	auto operator "" _fnv1a64(const wchar_t* str, size_t length)
	{
		return ::Core_TStringHash<wchar_t, TFNV1aHash<uint64> >(str, length);
	}

	auto operator "" _fnv1a64(const char16_t* str, size_t length)
	{
		return ::Core_TStringHash<char16_t, TFNV1aHash<uint64> >(str, length);
	}

	auto operator "" _fnv1a64(const char32_t* str, size_t length)
	{
		return ::Core_TStringHash<char32_t, TFNV1aHash<uint64> >(str, length);
	}
}

