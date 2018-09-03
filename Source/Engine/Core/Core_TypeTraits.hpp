#pragma once

#include "Core.hpp"
#include "Core_String.hpp"
#include "Core_FixedString.hpp"
#include "Core_StringHash.hpp"
#include <type_traits>

namespace Alba
{
	using std::enable_if;
	using std::enable_if_t;
	using std::is_lvalue_reference;
	using std::is_lvalue_reference_v;
	using std::is_rvalue_reference;
	using std::is_rvalue_reference_v;
	using std::is_integral;
	using std::is_integral_v;
	using std::is_floating_point;
	using std::is_floating_point_v;
	using std::is_same;
	using std::is_same_v;
	using std::common_type;
	using std::common_type_t;
	using std::is_base_of;
	using std::is_base_of_v;

	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	is_string
		// Desc	:	Type trait for string types
		//-----------------------------------------------------------------------------------------
		template <typename T>
		struct is_string : public eastl::false_type
		{
		};

		template <typename TCharType, typename TAllocator>
		struct is_string < eastl::basic_string<TCharType, TAllocator> > : public std::true_type
		{
		};

		template
		<
			typename TCharType,
			size_t	 TCount,
			OverflowBehavior TOverflowBehavior,
			typename TOverflowAllocator
		>
		struct is_string <eastl::fixed_string<TCharType, TCount, TOverflowBehavior, TOverflowAllocator> > : public std::true_type
		{
		};

		template<class T>
		constexpr bool is_string_v = is_string<T>::value;
	}
}