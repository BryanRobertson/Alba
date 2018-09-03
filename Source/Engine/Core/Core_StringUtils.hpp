//-------------------------------------------------------------------------------------------------
// Name	:	Core_StringUtils.hpp
// Desc	:	String formatting utility functions
//-------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include "Core_String.hpp"
#include "Core_FixedString.hpp"
#include "Core_StringView.hpp"
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
				//================================================================================
				static bool From(const StringView& aStringView, TDataType& aOutData)
				{
					return Convert(aStringView, aOutData);
				}

			protected:

				template <typename TCharType, typename TAllocator>
				static bool Convert(const StringView& aStringView, BasicString<TCharType, TAllocator>& aOutData)
				{
					aOutData.assign(aStringView.data(), aStringView.length());
					return true;
				}

				template <typename TCharType, size_t TCount, OverflowBehavior TOverflowBehavior, typename TOverflowAllocator>
				static bool Convert(const StringView& aStringView, FixedBasicString<TCharType, TCount, TOverflowBehavior, TOverflowAllocator>& aOutData)
				{
					aOutData.assign(aStringView.data(), aStringView.length());
					return true;
				}

				static bool Convert(const StringView& aStringView, int8& aOutData)
				{
					aOutData = static_cast<int8>(std::atoi(aStringView.data()));
					return true;
				}

				static bool Convert(const StringView& aStringView, uint8& aOutData)
				{
					aOutData = static_cast<uint8>(std::atoi(aStringView.data()));
					return true;
				}

				static bool Convert(const StringView& aStringView, int16& aOutData)
				{
					aOutData = static_cast<int16>(std::atoi(aStringView.data()));
					return true;
				}

				static bool Convert(const StringView& aStringView, uint16& aOutData)
				{
					aOutData = static_cast<uint16>(std::atoi(aStringView.data()));
					return true;
				}

				static bool Convert(const StringView& aStringView, int32& aOutData)
				{
					aOutData = static_cast<int32>(std::atoi(aStringView.data()));
					return true;
				}

				static bool Convert(const StringView& aStringView, uint32& aOutData)
				{
					aOutData = static_cast<uint32>(std::atoi(aStringView.data()));
					return true;
				}

				static bool Convert(const StringView& aStringView, int64& aOutData)
				{
					aOutData = static_cast<int64>(std::atoll(aStringView.data()));
					return true;
				}

				static bool Convert(const StringView& aStringView, uint64& aOutData)
				{
					aOutData = static_cast<uint64>(std::atoll(aStringView.data()));
					return true;
				}

				static bool Convert(const StringView& aStringView, bool& aOutData)
				{
					uint value = 0;
					if (Convert(aStringView, value))
					{
						aOutData = value != 0;
						return true;
					}

					auto locCaseInsensitiveCompare = [](char left, char right)
					{
						return std::tolower(left) == std::tolower(right);
					};

					const FixedString<8> fixedStr(aStringView.data());
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