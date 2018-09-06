#pragma once

//------------------------------------------------------------------------------------------------
// Name      :	Core_EnumerationSet.hpp
// Desc      :	Container acting as a set of enumeration values for a particular enumeration type.
//
//				Supports typical set operations (intersection, difference, union)
//
//				Implemented internally as a static bitset, where each bit represents the 
//				presence of a particular valid enumeration value.
//
//				Can be used to implement a strongly-typed set of bitflags, typed on an enumeration
//				where the low-level bit manipulation is hidden from the user.
//				(Obviously it's not well suited if you want control over the actual bit values,
//				 since this is handled internally)
//
//				Note: 
//					At the time of writing, this type relies on get_all_enum_values<T>
//					having been manually specialised for the relevant enumeration type.
//
//					In future - this could be automated via code-generation
//					(or reflection, if supported by a future C++ standard)
//
// Author    : Bryan Robertson
// Date      : 2018/09/05
//------------------------------------------------------------------------------------------------
#include "Core.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_EnumerationTraits.hpp"
#include "Core_Utils.hpp"
#include "Core_Bitset.hpp"

namespace Alba
{
	namespace Core
	{
		namespace Detail
		{
			using namespace ::Alba::BasicTypes;

			//-------------------------------------------------------------------------------------
			// Name	:	best_bitset_element_size
			// Desc	:	Based on an input value, return the best size to use for the internal
			//			values of the bitset
			//-------------------------------------------------------------------------------------
			template <size_t TEnumerationEntryCount>
			struct best_bitset_element_size
			{
				static constexpr size_t value = sizeof(size_t);
				typedef uint64 value_type;
			};

			template <>
			struct best_bitset_element_size<1>
			{
				static constexpr size_t value = 1;
				typedef uint8 value_type;
			};

			template <>
			struct best_bitset_element_size<2>
			{
				static constexpr size_t value = 2;
				typedef uint16 value_type;
			};

			template <>
			struct best_bitset_element_size<4>
			{
				static constexpr size_t value = 4;
				typedef uint32 value_type;
			};

			template <>
			struct best_bitset_element_size<8>
			{
				static constexpr size_t value = 8;
				typedef uint64 value_type;
			};

			template <typename TEnumerationType, class = enable_if_t<is_enum_v<TEnumerationType>> >
			static constexpr size_t best_bitset_element_size_v = best_bitset_element_size
			<
				NextLargestPowerOfTwo(get_enum_entry_count_v<TEnumerationType>)
			>
			::value;

			template <typename TEnumerationType, class = enable_if_t<is_enum_v<TEnumerationType>> >
			using best_bitset_element_type_t = best_bitset_element_size
			<
				NextLargestPowerOfTwo(get_enum_entry_count_v<TEnumerationType>)
			>
			::value_type;
		}

		//-----------------------------------------------------------------------------------------
		// Name	:	EnumerationSet
		//-----------------------------------------------------------------------------------------
		template <typename TEnumerationType, class=enable_if_t<is_enum_v<TEnumerationType>> >
		class EnumerationSet
		{
			public:

				//=================================================================================
				// Public Constants
				//=================================================================================
				static constexpr size_t ElementCount	= get_enum_entry_count_v<TEnumerationType>;
				static constexpr size_t ElementSize		= Detail::best_bitset_element_size_v<TEnumerationType>;

				//=================================================================================
				// Public Types
				//=================================================================================
				typedef Detail::best_bitset_element_type_t<TEnumerationType> ElementType;
				typedef BitSet<ElementCount, ElementType>					 BitSetType;

				//=================================================================================
				// Public Constructors
				//=================================================================================
				inline constexpr EnumerationSet();
				inline constexpr EnumerationSet(TEnumerationType aValue); // Implicit intentionally
				inline constexpr EnumerationSet(std::initializer_list<TEnumerationType> anInitList);

				inline constexpr EnumerationSet(const EnumerationSet<TEnumerationType>&) = default;
				inline constexpr EnumerationSet(EnumerationSet<TEnumerationType>&&) = default;

				//=================================================================================
				// Public Methods
				//=================================================================================

				//---------------------------------------------------------------------------------
				// operator~ 
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet<TEnumerationSet>& operator~ ();

				//---------------------------------------------------------------------------------
				// operator^=
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet<TEnumerationSet>& operator^= (const EnumerationSet<TEnumerationType>& aRhs);

				//---------------------------------------------------------------------------------
				// operator|= 
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet<TEnumerationSet>& operator|= (const EnumerationSet<TEnumerationType>& aRhs);

				//---------------------------------------------------------------------------------
				// operator&= 
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet<TEnumerationSet>& operator&= (const EnumerationSet<TEnumerationType>& aRhs);

				//---------------------------------------------------------------------------------
				// operator= , operator==
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet<TEnumerationType>& operator=(const EnumerationSet<TEnumerationType>&) = default;
				inline constexpr EnumerationSet<TEnumerationType>& operator=(EnumerationSet<TEnumerationType>&&) = default;

				inline constexpr bool operator==(const EnumerationSet<TEnumerationType>&) = default;
				inline constexpr bool operator!=(const EnumerationSet<TEnumerationType>&) = default;

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				BitSetType	myData;
		};
	}
}