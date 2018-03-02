#pragma once

#include <EASTL/type_traits.h>
#include "Core_String.hpp"
#include "Core_FixedString.hpp"

namespace Alba
{
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
		struct is_string < eastl::basic_string<TCharType, TAllocator> > : public eastl::true_type
		{
		};

		template
		<
			typename TCharType,
			size_t	 TCount,
			OverflowBehavior TOverflowBehavior,
			typename TOverflowAllocator
		>
		struct is_string <eastl::fixed_string<TCharType, TCount, TOverflowBehavior, TOverflowAllocator> > : public eastl::true_type
		{
		};
	}
}