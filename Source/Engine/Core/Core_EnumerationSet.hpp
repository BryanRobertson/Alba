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
//					At the time of writing, this type relies on EnumerationTraits<T>
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
#include "Core_Bitset.hpp"
#include "Core_Utils.hpp"

namespace Alba
{
	namespace Core
	{
		namespace Detail
		{
			//-------------------------------------------------------------------------------------
			// Name	:	BestBitsetElementSize
			// Desc	:	Based on an input value, return the best size to use for the internal
			//			values of the bitset
			//-------------------------------------------------------------------------------------
			template <size_t TEnumerationEntryCount>
			struct BestBitsetElementSize
			{
				static constexpr size_t Value = sizeof(size_t);
				typedef uint64 ElementType;
			};

			template <>
			struct BestBitsetElementSize<1>
			{
				static constexpr size_t Value = 1;
				typedef uint8 ElementType;
			};

			template <>
			struct BestBitsetElementSize<2>
			{
				static constexpr size_t Value = 2;
				typedef uint16 ElementType;
			};

			template <>
			struct BestBitsetElementSize<4>
			{
				static constexpr size_t Value = 4;
				typedef uint32 ElementType;
			};

			template <>
			struct BestBitsetElementSize<8>
			{
				static constexpr size_t Value = 8;
				typedef uint64 ElementType;
			};
		} 

		//-----------------------------------------------------------------------------------------
		// Name	:	EnumerationSet
		//-----------------------------------------------------------------------------------------
		template <typename TEnumerationType, class=enable_if<is_enum_v<TEnumerationType> >
		class EnumerationSet
		{
			public:

				//=================================================================================
				// Public Types
				//=================================================================================

				//=================================================================================
				// Public Constructors
				//=================================================================================

				//=================================================================================
				// Public Methods
				//=================================================================================
		};
	}
}