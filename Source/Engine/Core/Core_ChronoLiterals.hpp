#pragma once

#include "Core.hpp"
#include "Core_Time.hpp"

namespace Alba
{
	namespace ChronoLiterals
	{
		inline constexpr auto operator "" _days(unsigned long long aCount)
		{
			return Alba::Core::Duration<uint64, std::ratio<60 * 60 * 24>>(aCount);
		}

		inline constexpr auto operator "" _days(long double aCount)
		{
			return Alba::Core::Duration<float, std::ratio<60 * 60 * 24>>(aCount);
		}

		inline constexpr auto operator "" _hours(unsigned long long aCount)
		{
			return Alba::Core::Duration<uint64, std::chrono::hours::period>(aCount);
		}

		inline constexpr auto operator "" _hours(long double aCount)
		{
			return Alba::Core::Duration<float, std::chrono::hours::period>(aCount);
		}

		inline constexpr auto operator "" _seconds(long double aCount)
		{
			return Alba::Core::Duration<float, std::ratio<1, 1>>(static_cast<float>(aCount));
		}

		inline constexpr auto operator "" _seconds(unsigned long long aCount)
		{
			return Alba::Core::Duration<uint64, std::ratio<1, 1>>(static_cast<uint64>(aCount));
		}

		inline constexpr auto operator "" _milliseconds(unsigned long long aCount)
		{
			return Alba::Core::Duration<uint64, std::milli>(static_cast<uint64>(aCount));
		}

		inline constexpr auto operator "" _milliseconds(long double aCount)
		{
			return Alba::Core::Duration<float, std::milli>(static_cast<float>(aCount));
		}

		inline constexpr auto operator "" _nanoseconds(unsigned long long aCount)
		{
			return Alba::Core::Duration<uint64, std::nano>(static_cast<uint64>(aCount));
		}

		inline constexpr auto operator "" _nanoseconds(long double aCount)
		{
			return Alba::Core::Duration<float, std::nano>(static_cast<float>(aCount));
		}
	}
}