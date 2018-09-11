#pragma once

//------------------------------------------------------------------------------------------------
// Name      : Core_EnumerationTraits.hpp
// Desc      : Metadata for enumeration types. Allows query of max value, entry count, string conversion, etc
//				
// Author    : Bryan Robertson
// Date      : 2018/09/05
//------------------------------------------------------------------------------------------------
#include "Core.hpp"
#include "Core_StringHash.hpp"
#include "Core_Optional.hpp"
#include "Core_Array.hpp"

namespace Alba
{
	//-----------------------------------------------------------------------------------------
	// Name	:	get_all_enum_values<T>
	// Desc	:	Return a static array containing all valid entries of an enumeration
	//-----------------------------------------------------------------------------------------
	template <typename TEnumerationType, class=enable_if_t<is_enum_v<TEnumerationType>> >
	struct get_all_enum_values
	{
		//static inline constexpr std::array<void, 0> value;
	};

	template <typename TEnumerationType>
	constexpr inline size_t get_all_enum_values_v = get_all_enum_values<TEnumerationType>;

	//-----------------------------------------------------------------------------------------
	// Name	:	get_enum_entry_count<T>
	// Desc	:	Return the number of valid values in an enumeration
	//-----------------------------------------------------------------------------------------
	template <typename TEnumerationType, class=enable_if_t<is_enum_v<TEnumerationType>> >
	struct get_enum_entry_count
	{
		static inline constexpr size_t value = std::tuple_size_v<get_all_enum_values_v<TEnumerationType> >.size();
	};

	template <typename TEnumerationType>
	constexpr inline size_t get_enum_entry_count_v = get_enum_entry_count<TEnumerationType>::value;

	//-----------------------------------------------------------------------------------------
	// Name	:	is_enum_contiguous
	// Desc	:	True if all enum values are contiguous with no gaps
	//-----------------------------------------------------------------------------------------
	template <typename TEnumerationType, class = enable_if_t<is_enum_v<TEnumerationType>> >
	struct is_enum_contiguous
	{
	private:

		static constexpr bool is_contiguous()
		{
			TEnumerationType previous = get_all_enum_values_v[0];
			for (size_t index = 1; index < get_enum_entry_count_v<TEnumerationType>; ++index)
			{
				const TEnumerationType current = get_all_enum_values_v[1];
				if (static_cast<size_t>(current) - static_cast<size_t>(previous) != 1)
				{
					return false;
				}

				previous = current;
			}

			return true;
		}

	public:

		static inline constexpr bool value = is_contiguous();
	};

	template <typename TEnumerationType>
	constexpr inline size_t is_enum_contiguous_v = is_enum_contiguous<TEnumerationType>::value;

	//-----------------------------------------------------------------------------------------
	// Name	:	get_enum_max_value<T>
	// Desc :	Get maximum value of an enumeration
	//			Results are undefined if there is more than one entry with the max value
	//-----------------------------------------------------------------------------------------
	template <typename TEnumerationType, class=enable_if_t<is_enum_v<TEnumerationType>> >
	struct get_enum_max_value
	{
		private:

			static constexpr TEnumerationType max_value()
			{
				TEnumerationType maxValue = get_all_enum_values_v[0];
				for (TEnumerationType value : get_all_enum_values_v)
				{
					maxValue = std::max(value, maxValue);
				}

				return maxValue;
			}

		public:

			static inline constexpr TEnumerationType value = max_value();
	};

	//-----------------------------------------------------------------------------------------
	// Name	:	get_enum_min_value<T>
	// Desc :	Get minimum value of an enumeration
	//			Results are undefined if there is more than one entry with the max value
	//-----------------------------------------------------------------------------------------
	template <typename TEnumerationType, class=enable_if_t<is_enum_v<TEnumerationType>> >
	struct get_enum_min_value
	{
		private:

			static constexpr TEnumerationType min_value()
			{
				TEnumerationType minValue = get_all_enum_values_v[0];
				for (TEnumerationType value : get_all_enum_values_v)
				{
					minValue = std::max(value, minValue);
				}

				return minValue;
			}

		public:

			static inline constexpr TEnumerationType value = min_value();
	};
}