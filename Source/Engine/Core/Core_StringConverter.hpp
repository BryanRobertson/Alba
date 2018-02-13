#pragma once

#include "Core_API.hpp"
#include "Core_BasicTypes.hpp"

#include <cstdio>

namespace Alba
{
	namespace Core
	{
		//-------------------------------------------------------------------------------------------------
		// Name	:	StringConverter
		// Desc	:	Convert TValueType to a string
		//-------------------------------------------------------------------------------------------------
		template <typename TStringType, typename TValueType>
		class StringConverter
		{
			public:

				typedef typename TStringType::value_type	CharType;

				//=========================================================================================
				// Public Static Methods
				//=========================================================================================
				static bool ToString(const TValueType& aValue, TStringType& outString)
				{
					return true;
				}

				static bool ToString(uint8 aValue, TStringType& outString)
				{
					return WriteFormattedToString("%u", aValue, outString);
				}

				static bool ToString(int8 aValue, TStringType& outString)
				{
					return WriteFormattedToString("%d", aValue, outString);
				}

				static bool ToString(uint16 aValue, TStringType& outString)
				{
					return WriteFormattedToString("%u", aValue, outString);
				}

				static bool ToString(int16 aValue, TStringType& outString)
				{
					return WriteFormattedToString("%d", aValue, outString);
				}

				static bool ToString(uint32 aValue, TStringType& outString)
				{
					return WriteFormattedToString("%u", aValue, outString);
				}

				static bool ToString(int32 aValue, TStringType& outString)
				{
					return WriteFormattedToString("%d", aValue, outString);
				}

				static bool ToString(uint64 aValue, TStringType& outString)
				{
					return WriteFormattedToString("%ul", aValue, outString);
				}

				static bool ToString(int64 aValue, TStringType& outString)
				{
					return WriteFormattedToString("%dl", aValue, outString);
				}

				template <typename TValueType>
				static bool WriteFormattedToString(const CharType* aFormat, const TValueType& aValue, TStringType& outString)
				{
					const size_t capacity = outString.capacity();
					const CharType* buffer = &outString[0];

					const int actualSize = std::snprintf(buffer, capacity, aFormat, aValue);
					if (actualSize < 0)
					{
						return false;
					}

					if (actualSize > capacity)
					{
						outString.reserve(actualSize);
					}

					return std::snprintf(buffer, outString.capacity(), aFormat, aValue) == capacity;
				}
		};
	}
}
