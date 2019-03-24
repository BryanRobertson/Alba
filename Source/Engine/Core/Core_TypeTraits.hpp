#pragma once

#include "Core.hpp"
#include "Core_String.hpp"
#include "Core_FixedString.hpp"
#include "Core_StringHash.hpp"
#include "Core_Container.hpp"
#include <type_traits>
#include <EASTL/iterator.h>

namespace Alba
{
	using std::enable_if;
	using std::enable_if_t;
	using std::is_enum;
	using std::is_enum_v;
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
	using std::is_signed;
	using std::is_signed_v;
	using std::common_type;
	using std::common_type_t;
	using std::is_base_of;
	using std::is_base_of_v;
	using std::is_invocable;
	using std::is_invocable_v;
	using std::is_invocable_r;
	using std::is_invocable_r_v;
	using std::is_member_function_pointer;
	using std::is_member_function_pointer_v;
	using std::is_move_assignable;
	using std::is_move_assignable_v;
	using std::is_move_constructible;
	using std::is_move_constructible_v;;
	using std::is_nothrow_invocable;
	using std::is_nothrow_assignable_v;
	using std::is_standard_layout;
	using std::is_standard_layout_v;
	using std::extent;
	using std::extent_v;
	using std::true_type;
	using std::false_type;
	using eastl::iterator_traits;
	using eastl::distance;

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
		typename	TCharType,
		size_t		TCount,
		bool		TEnableOverflow,
		typename	TOverflowAllocator
	>
	struct is_string <eastl::fixed_string<TCharType, TCount, TEnableOverflow, TOverflowAllocator> > : public std::true_type
	{
	};

	template<class T>
	constexpr bool is_string_v = is_string<T>::value;
}