//-------------------------------------------------------------------------------------------------
// Name	:	Core_StringUtils.hpp
// Desc	:	String formatting utility functions
//-------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include "Core_String.hpp"
#include "Core_FixedString.hpp"
#include "Core_Utils.hpp"

#include <cstdlib>

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		constexpr uint64 GetBestFixedStringSize(uint64 anInputSize)
		{
			return (NextLargestPowerOfTwo(anInputSize) - anInputSize) <= 512
					? NextLargestPowerOfTwo(anInputSize)
					: anInputSize;
		}

		//-----------------------------------------------------------------------------------------
		// Name	:	FormatString
		//-----------------------------------------------------------------------------------------
		template <size_t TFixedStringSize, typename... TArgs>
		FixedString<GetBestFixedStringSize(TFixedStringSize)> FormatString(const char* const format, TArgs&&... args)
		{
			typedef FixedString<GetBestFixedStringSize(TFixedStringSize)> StringType;
			return StringType( StringType::CtorSprintf(), format, std::forward<TArgs>(args)...);
		}

		template <typename... TArgs>
		String FormatString(const char* const format, TArgs&&... args)
		{
			return String(String::CtorSprintf(), format, std::format(args)...);
		}

		//-----------------------------------------------------------------------------------------
		// Name	:	StringConverter
		//-----------------------------------------------------------------------------------------
		template <typename TDataType>
		class StringConverter
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				template <typename TCharType, typename TAllocator>
				static bool From(const BasicString<TCharType, TAllocator>& aString, TDataType& aOutData)
				{
					return Convert(aString.c_str(), aOutData);
				}

			protected:

				template <typename TCharType, typename TAllocator>
				static bool Convert(const char* aString, BasicString<TCharType, TAllocator>& aOutData)
				{
					aOutData.assign(aString);
					return true;
				}

				static bool Convert(const char* aString, int8& aOutData)
				{
					aOutData = static_cast<int8>(std::atoi(aString));
					return true;
				}

				static bool Convert(const char* aString, uint8& aOutData)
				{
					aOutData = static_cast<uint8>(std::atoi(aString));
					return true;
				}

				static bool Convert(const char* aString, int16& aOutData)
				{
					aOutData = static_cast<int16>(std::atoi(aString));
					return true;
				}

				static bool Convert(const char* aString, uint16& aOutData)
				{
					aOutData = static_cast<uint16>(std::atoi(aString));
					return true;
				}

				static bool Convert(const char* aString, int32& aOutData)
				{
					aOutData = static_cast<int32>(std::atoi(aString));
					return true;
				}

				static bool Convert(const char* aString, uint32& aOutData)
				{
					aOutData = static_cast<uint32>(std::atoi(aString));
					return true;
				}

				static bool Convert(const char* aString, int64& aOutData)
				{
					aOutData = static_cast<int64>(std::atoll(aString));
					return true;
				}

				static bool Convert(const char* aString, uint64& aOutData)
				{
					aOutData = static_cast<uint64>(std::atoll(aString));
					return true;
				}

				static bool Convert(const char* aString, bool& aOutData)
				{
					uint value = 0;
					if (Convert(aString, value))
					{
						aOutData = value != 0;
						return true;
					}

					auto locCaseInsensitiveCompare = [](char left, char right)
					{
						return std::tolower(left) == std::tolower(right);
					};

					const FixedString<8> fixedStr(aString);

					static const FixedString<8> trueStr("true");
					if (fixedStr.comparei(trueStr))
					{
						aOutData = true;
						return true;
					}

					static const FixedString<8> falseStr("false");
					if (fixedStr.comparei(falseStr))
					{
						aOutData = false;
						return true;
					}


					return false;
				}
		};
	}
}