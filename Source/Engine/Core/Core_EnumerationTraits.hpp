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
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	get_all_enum_values<T>
		// Desc	:	Return a static array containing all valid entries of an enumeration
		//-----------------------------------------------------------------------------------------
		template <typename TEnumerationType, class=enable_if_t<is_enum_v<TEnumerationType>> >
		struct get_all_enum_values
		{
			static inline constexpr std::array<void> value;
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