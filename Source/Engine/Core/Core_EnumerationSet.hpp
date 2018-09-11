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
				::Alba::Core::NextLargestPowerOfTwo(::Alba::Core::get_enum_entry_count_v<TEnumerationType>)
			>
			::value;

			template <typename TEnumerationType, class = enable_if_t<is_enum_v<TEnumerationType>> >
			using best_bitset_element_type_t = typename best_bitset_element_size
			<
				::Alba::Core::NextLargestPowerOfTwo(::Alba::Core::get_enum_entry_count_v<TEnumerationType>)
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
				inline constexpr EnumerationSet() = default;
				inline constexpr EnumerationSet(TEnumerationType aValue); // Implicit intentionally
				inline constexpr EnumerationSet(std::initializer_list<TEnumerationType> anInitList);

				inline constexpr EnumerationSet(const EnumerationSet<TEnumerationType>&) = default;
				inline constexpr EnumerationSet(EnumerationSet<TEnumerationType>&&) = default;

				//=================================================================================
				// Public Methods
				//=================================================================================

				//---------------------------------------------------------------------------------
				// Add / Remove / Clear / Contains / Count
				//---------------------------------------------------------------------------------
				inline constexpr void	Insert(TEnumerationType aValue);
				inline constexpr void	Insert(std::initializer_list<TEnumerationType> anInitList);

				inline constexpr void	Remove(TEnumerationType aValue);
				inline constexpr void	Clear();

				inline constexpr bool	Contains(TEnumerationType aValue) const;
				inline constexpr size_t Count() const;

				//---------------------------------------------------------------------------------
				// operator~ 
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet<TEnumerationSet>& operator~ ();

				//---------------------------------------------------------------------------------
				// operator^=
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet<TEnumerationSet>& operator^= (const EnumerationSet<TEnumerationType, >& aRhs);

				//---------------------------------------------------------------------------------
				// operator|= 
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet<TEnumerationSet>& operator|= (const EnumerationSet<TEnumerationType, >& aRhs);

				//---------------------------------------------------------------------------------
				// operator&= 
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet<TEnumerationSet>& operator&= (const EnumerationSet<TEnumerationType, >& aRhs);

				//---------------------------------------------------------------------------------
				// operator= , operator==, operator!=
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet<TEnumerationType>& operator=(const EnumerationSet<TEnumerationType, >&) = default;
				inline constexpr EnumerationSet<TEnumerationType>& operator=(EnumerationSet<TEnumerationType, >&&) = default;

				inline constexpr EnumerationSet<TEnumerationType>& operator=(std::initializer_list<TEnumerationType> anInitList);

				inline constexpr bool operator==(const EnumerationSet<TEnumerationType>&) = default;
				inline constexpr bool operator!=(const EnumerationSet<TEnumerationType>&) = default;

				//---------------------------------------------------------------------------------
				// Iterators
				//---------------------------------------------------------------------------------
				class ConstIterator
				{
					public:

						friend class EnumerationSet<TEnumerationType>;

						using iterator_category = std::forward_iterator_tag;
						using value_type		= TEnumerationType;
						using difference_type	= std::ptrdiff_t;
						using pointer			= TEnumerationType*;
						using reference			= TEnumerationType&;

						//-------------------------------------------------------------------------
						//-------------------------------------------------------------------------
						ConstIterator() = default;

						//-------------------------------------------------------------------------
						//-------------------------------------------------------------------------
						inline ConstIterator& operator++();
						inline ConstIterator operator++(int);

						inline ConstIterator& operator=(const ConstIterator& aCopyFrom) = default;
						inline ConstIterator& operator=(ConstIterator&& aMoveFrom) = default;

						inline bool operator<(const ConstIterator& aRhs) const;
						inline bool operator>(const ConstIterator& aRhs) const;
						inline bool operator<=(const ConstIterator& aRhs) const;
						inline bool operator>=(const ConstIterator& aRhs) const;
						inline bool operator==(const ConstIterator& aRhs) const = default;
						inline bool operator!=(const ConstIterator& aRhs) const = default;

						TEnumerationType operator*() const;

					private:

						//-------------------------------------------------------------------------
						//-------------------------------------------------------------------------
						ConstIterator(size_t anIndex, EnumerationSet<TEnumerationType>& aCollection)
							: myIndex(anIndex)
							, myCollection(&aCollection)
						{

						}

						//-------------------------------------------------------------------------
						//-------------------------------------------------------------------------
						inline constexpr void Advance();

						//-------------------------------------------------------------------------
						//-------------------------------------------------------------------------
						size_t							  myIndex = 0;
						EnumerationSet<TEnumerationType>* myCollection = nullptr;
				};

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				
				//-------------------------------------------------------------------------
				//-------------------------------------------------------------------------
				static constexpr size_t GetIndex(TEnumerationType aValue) const
				{
					if constexpr (is_enum_contiguous_v<TEnumerationType>)
					{
						return static_cast<TEnumerationType>
						(
							static_cast<size_t>(aValue) - static_cast<size_t>(get_all_enum_values_v<TEnumerationType>[0])
						);
					}
					else
					{
						size_t index = 0;
						for (TEnumerationType entry : get_all_enum_values_v<TEnumerationType>)
						{
							if (entry == aValue)
							{
								return index;
							}

							++index;
						}

						ALBA_ASSERT(false, "Invalid enumeration value!");
						return index;
					}
				}

				//=================================================================================
				// Private Data
				//=================================================================================
				BitSetType	myData;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TEnumerationType, >
		/*inline*/ constexpr EnumerationSet<TEnumerationType, >::EnumerationSet(TEnumerationType aValue)
		{
			Insert(aValue);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TEnumerationType, >
		/*inline*/ constexpr EnumerationSet<TEnumerationType, >::EnumerationSet(std::initializer_list<TEnumerationType> anInitList)
		{
			for (TEnumerationType aValue : anInitList)
			{
				Insert(aValue);
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		/*inline*/ constexpr void EnumerationSet<TEnumerationType, >::Insert(TEnumerationType aValue)
		{
			const size_t index = GetIndex(aValue);
			myData.set(index, true);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		/*inline*/ constexpr void EnumerationSet<TEnumerationType, >::Insert(std::initializer_list<TEnumerationType> anInitList)
		{
			for (TEnumerationType aValue : anInitList)
			{
				const size_t index = GetIndex(aValue);
				myData.set(index, true);
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		/*inline*/ constexpr void EnumerationSet<TEnumerationType, >::Remove(TEnumerationType aValue)
		{
			const size_t index = GetIndex(aValue);
			myData.set(index, false);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		/*inline*/ constexpr void EnumerationSet<TEnumerationType, >::Clear()
		{
			myData.reset();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		/*inline*/ constexpr bool EnumerationSet<TEnumerationType, >::Contains(TEnumerationType aValue) const
		{
			const size_t index = GetIndex(aValue);
			return false;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		/*inline*/ constexpr size_t EnumerationSet<TEnumerationType, >::Count() const
		{
			size_t bitSetCount = 0;

			for (size_t index = 0; index < BitSetType::kWordCount; ++index)
			{
				size_t v = myData.data()[index];
				while (v)
				{
					v = v & v - 1;
					++bitSetCount;
				}
			}

			return bitSetCount;
			
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		/*inline*/ constexpr EnumerationSet<TEnumerationSet>& EnumerationSet<TEnumerationType, >::operator~()
		{
			myData = ~myData;
			return *this;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		inline constexpr EnumerationSet<TEnumerationSet>& EnumerationSet<TEnumerationType, >::operator^=(const EnumerationSet<TEnumerationType>& aRhs)
		{
			myData ^= aRHS.myData;
			return *this;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		inline constexpr EnumerationSet<TEnumerationSet>& EnumerationSet<TEnumerationType, >::operator|=(const EnumerationSet<TEnumerationType>& aRhs)
		{
			myData |= aRHS.myData;
			return *this;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		inline constexpr EnumerationSet<TEnumerationSet>& EnumerationSet<TEnumerationType, >::operator&=(const EnumerationSet<TEnumerationType>& aRhs)
		{
			myData &= aRHS.myData;
			return *this;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		inline constexpr EnumerationSet<TEnumerationType>& EnumerationSet<TEnumerationType, >::operator=(std::initializer_list<TEnumerationType> anInitList)
		{
			*this = EnumerationSet<TEnumerationType>(std::forward<std::initializer_set<TEnumerationType>(anInitList));
			return *this;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TEnumerationType, class T>
		/*inline*/ EnumerationSet<TEnumerationType, T> operator^(const EnumerationSet<TEnumerationType, T>& aLHS, const EnumerationSet<TEnumerationType, T>& aRHS)
		{
			EnumerationSet<TEnumerationType> result = aLHS;
			result ^= aRHS;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TEnumerationType, class T>
		/*inline*/ EnumerationSet<TEnumerationType, T> operator&(const EnumerationSet<TEnumerationType, T>& aLHS, const EnumerationSet<TEnumerationType, T>& aRHS)
		{
			EnumerationSet<TEnumerationType> result = aLHS;
			result &= aRHS;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TEnumerationType, class T>
		/*inline*/ EnumerationSet<TEnumerationType, T> operator|(const EnumerationSet<TEnumerationType, T>& aLHS, const EnumerationSet<TEnumerationType, T>& aRHS)
		{
			EnumerationSet<TEnumerationType> result = aLHS;
			result |= aRHS;
		}

		//=========================================================================================
		// Iterator
		//=========================================================================================

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		inline ConstIterator& EnumerationSet<TEnumerationType, >::ConstIterator::operator++()
		{
			Advance();
			return *this;			
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		inline ConstIterator EnumerationSet<TEnumerationType, >::ConstIterator::operator++(int)
		{
			ConstIterator result = *this;
			Advance();

			return result;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		inline void EnumerationSet<TEnumerationType, >::Advance()
		{
			++myIndex;
			while (myIndex < get_enum_entry_count_v<TEnumerationType>)
			{
				if (myCollection->Contains(get_all_enum_values_v[myIndex]))
				{
					return;
				}

				++myIndex;
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		inline bool EnumerationSet<TEnumerationType, >::ConstIterator::operator<(const ConstIterator & aRhs) const
		{
			return myIndex < aRhs.myIndex;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		inline bool EnumerationSet<TEnumerationType, >::ConstIterator::operator>(const ConstIterator & aRhs) const
		{
			return myIndex > aRhs.myIndex;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		inline bool EnumerationSet<TEnumerationType, >::ConstIterator::operator<=(const ConstIterator & aRhs) const
		{
			return myIndex <= aRhs.myIndex;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		inline bool EnumerationSet<TEnumerationType, >::ConstIterator::operator>=(const ConstIterator & aRhs) const
		{
			return myIndex >= aRhs.myIndex;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, >
		inline TEnumerationType EnumerationSet<TEnumerationType, >::ConstIterator::operator*() const
		{
			return get_all_enum_values_v<TEnumerationType>[myIndex];
		}
}
}