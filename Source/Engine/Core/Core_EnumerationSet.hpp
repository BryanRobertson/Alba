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
			//-------------------------------------------------------------------------------------
			// Name	:	best_bitset_element_size
			// Desc	:	Based on an input value, return the best size to use for the internal
			//			values of the bitset
			//-------------------------------------------------------------------------------------
			template <size_t TEnumerationEntryCount>
			struct best_bitset_element_size
			{
				static constexpr size_t value = sizeof(size_t);
				using value_type = uint64;
			};

			template <>
			struct best_bitset_element_size<1>
			{
				static constexpr size_t value = 1;
				using value_type = uint8;
			};

			template <>
			struct best_bitset_element_size<2>
			{
				static constexpr size_t value = 2;
				using value_type = uint16;
			};

			template <>
			struct best_bitset_element_size<4>
			{
				static constexpr size_t value = 4;
				using value_type = uint32;
			};

			template <>
			struct best_bitset_element_size<8>
			{
				static constexpr size_t value = 8;
				using value_type = uint64;
			};

			template <typename TEnumerationType, class = enable_if_t<is_enum_v<TEnumerationType>> >
			static constexpr size_t best_bitset_element_size_v = best_bitset_element_size
			<
				::Alba::Core::NextLargestPowerOfTwo(get_enum_entry_count_v<TEnumerationType> / 8)
			>
			::value;

			template <typename TEnumerationType, class = enable_if_t<is_enum_v<TEnumerationType>> >
			using best_bitset_element_type_t = typename best_bitset_element_size
			<
				::Alba::Core::NextLargestPowerOfTwo(get_enum_entry_count_v<TEnumerationType> / 8)
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

				static constexpr size_t ElementCount	= get_enum_entry_count_v<TEnumerationType>;
				static constexpr size_t ElementSize		= Detail::best_bitset_element_size_v<TEnumerationType>;

				//=================================================================================
				// Public Types
				//=================================================================================
				using ElementType	=  Detail::best_bitset_element_type_t<TEnumerationType>;
				using BitSetType	=  BitSet<ElementCount, ElementType>;

				//=================================================================================
				// Public Static Constants
				//=================================================================================
				static constexpr size_t BitSetBitsPerWord	= BitSetType::kBitsPerWord;
				static constexpr size_t BitSetWordCount		= ElementCount / BitSetBitsPerWord;
				static constexpr bool	IsContiguousEnum	= is_enum_contiguous_v<TEnumerationType>;

				//=================================================================================
				// Public Constructors
				//=================================================================================
				inline constexpr EnumerationSet() = default;
				inline constexpr EnumerationSet(const EnumerationSet& aCopyFrom) = default;
				inline constexpr EnumerationSet(EnumerationSet&& aMoveFrom) = default;
				inline constexpr EnumerationSet(std::initializer_list<TEnumerationType> anInitList);

				template <typename TIteratorType, class=enable_if<is_base_of_v<std::input_iterator_tag, typename TIteratorType::iterator_category> > >
				inline explicit constexpr EnumerationSet(const TIteratorType& aBegin, const TIteratorType& anEnd)
				{
					for (TIteratorType itr = aBegin; itr != anEnd; ++itr)
					{
						Insert(*itr);
					}
				}

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static constexpr EnumerationSet GetEmpty();
				static constexpr EnumerationSet GetAllEntries();

				//=================================================================================
				// Public Static Constants
				//=================================================================================
				static const EnumerationSet	Empty;
				static const EnumerationSet All;

				//=================================================================================
				// Public MethodsT
				//=================================================================================

				//---------------------------------------------------------------------------------
				// Get the underlying value of the bitset
				//---------------------------------------------------------------------------------
				template <class=enable_if_t<BitSetType::kWordCount == 1u>>
				constexpr ElementType GetBits() const
				{
					return myData.data()[0];
				}

				//---------------------------------------------------------------------------------
				// Add / Remove / Clear / Contains / Count
				//---------------------------------------------------------------------------------
				inline constexpr void	Insert(TEnumerationType aValue);
				inline constexpr void	Insert(std::initializer_list<TEnumerationType> anInitList);

				inline constexpr void	Remove(TEnumerationType aValue);
				inline constexpr void	Clear();

				inline constexpr void	Invert();

				inline constexpr bool	Contains(TEnumerationType aValue) const;
				inline constexpr size_t Count() const;

				inline constexpr size_t IsEmpty() const;

				//---------------------------------------------------------------------------------
				// Set Difference / Intersection / Union
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet Difference(const EnumerationSet& aSet) const;
				inline constexpr EnumerationSet Intersection(const EnumerationSet& aSet) const;
				inline constexpr EnumerationSet Union(const EnumerationSet& aSet) const;

				inline constexpr EnumerationSet& SetToDifference(const EnumerationSet& aSet)
				{
					*this = Difference(aSet);
					return *this;
				}

				inline constexpr EnumerationSet& SetToIntersection(const EnumerationSet& aSet)
				{
					*this = Intersection(aSet);
					return *this;
				}

				inline constexpr EnumerationSet& SetToUnion(const EnumerationSet& aSet)
				{
					*this = Union(aSet);
					return *this;
				}

				//---------------------------------------------------------------------------------
				// operator~ 
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet operator~ () const;

				//---------------------------------------------------------------------------------
				// operator^=
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet& operator^= (const EnumerationSet& aRight);

				//---------------------------------------------------------------------------------
				// operator-= 
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet& operator-= (const EnumerationSet& aRight);

				//---------------------------------------------------------------------------------
				// operator|= 
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet& operator|= (const EnumerationSet& aRight);

				//---------------------------------------------------------------------------------
				// operator&= 
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet& operator&= (const EnumerationSet& aRight);

				//---------------------------------------------------------------------------------
				// operator= , operator==, operator!=
				//---------------------------------------------------------------------------------
				inline constexpr EnumerationSet& operator=(const EnumerationSet&) = default;
				inline constexpr EnumerationSet& operator=(EnumerationSet&&) = default;

				inline constexpr EnumerationSet& operator=(std::initializer_list<TEnumerationType> anInitList);

				inline constexpr bool operator==(const EnumerationSet&) const;
				inline constexpr bool operator!=(const EnumerationSet&) const;

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
						ConstIterator(const ConstIterator& aCopyFrom) = default;
						ConstIterator(ConstIterator&& aMoveFrom) = default;

						//-------------------------------------------------------------------------
						//-------------------------------------------------------------------------
						inline ConstIterator& operator++();
						inline ConstIterator operator++(int);

						inline ConstIterator& operator=(const ConstIterator& aCopyFrom) = default;
						inline ConstIterator& operator=(ConstIterator&& aMoveFrom) = default;

						inline bool operator<(const ConstIterator& aRight) const;
						inline bool operator>(const ConstIterator& aRight) const;
						inline bool operator<=(const ConstIterator& aRight) const;
						inline bool operator>=(const ConstIterator& aRight) const;
						inline bool operator==(const ConstIterator& aRight) const;
						inline bool operator!=(const ConstIterator& aRight) const;

						TEnumerationType operator*() const;

					private:

						//-------------------------------------------------------------------------
						//-------------------------------------------------------------------------
						ConstIterator(size_t anIndex, const EnumerationSet<TEnumerationType>& aCollection)
							: myIndex(anIndex)
							, myCollection(&aCollection)
						{

						}

						//-------------------------------------------------------------------------
						//-------------------------------------------------------------------------
						inline constexpr void Advance();

						//-------------------------------------------------------------------------
						//-------------------------------------------------------------------------
						size_t									myIndex = 0;
						const EnumerationSet<TEnumerationType>* myCollection = nullptr;
				};

				ConstIterator begin() const;
				ConstIterator end() const;

				ConstIterator cbegin() const;
				ConstIterator cend() const;

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				
				//-------------------------------------------------------------------------
				//-------------------------------------------------------------------------
				static constexpr size_t GetIndex(TEnumerationType aValue)
				{
					if constexpr (is_enum_contiguous_v<TEnumerationType>)
					{
						return static_cast<size_t>(aValue) - static_cast<size_t>(get_all_enum_values_v<TEnumerationType>[0]);
					}
					else
					{
						size_t index = 0;

						static constexpr auto& allValues = get_all_enum_values_v<TEnumerationType>;
						for (TEnumerationType entry : allValues)
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

#if !defined(ALBA_RETAIL_BUILD)

				//-------------------------------------------------------------------------
				// Used only for Visual Studio .natvis
				//-------------------------------------------------------------------------
				static constexpr TEnumerationType GetValueAtIndex(size_t anIndex)
				{
					static constexpr auto& allValues = get_all_enum_values_v<TEnumerationType>;
					return allValues[anIndex];
				}
#endif

				//=================================================================================
				// Private Data
				//=================================================================================
				BitSetType	myData;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TEnumerationType, class T>
		/*static*/ const EnumerationSet<TEnumerationType, T> EnumerationSet<TEnumerationType, T>::Empty = EnumerationSet<TEnumerationType, T>::GetEmpty();

		template <typename TEnumerationType, class T>
		/*static*/ const EnumerationSet<TEnumerationType, T> EnumerationSet<TEnumerationType, T>::All = EnumerationSet<TEnumerationType, T>::GetAllEntries();

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TEnumerationType, class T>
		/*inline*/ constexpr EnumerationSet<TEnumerationType, T>::EnumerationSet(std::initializer_list<TEnumerationType> anInitList)
		{
			Insert(anInitList);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		inline constexpr EnumerationSet<TEnumerationType, T> EnumerationSet<TEnumerationType, T>::GetEmpty()
		{
			return EnumerationSet();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		inline constexpr EnumerationSet<TEnumerationType, T> EnumerationSet<TEnumerationType, T>::GetAllEntries()
		{
			EnumerationSet result;
			for (TEnumerationType value : get_all_enum_values<TEnumerationType>::value)
			{
				result.Insert(value);
			}

			return result;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr void EnumerationSet<TEnumerationType, T>::Insert(TEnumerationType aValue)
		{
			const size_t index = GetIndex(aValue);
			myData.set(index, true);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr void EnumerationSet<TEnumerationType, T>::Insert(std::initializer_list<TEnumerationType> anInitList)
		{
			for (auto itr = anInitList.begin(); itr != anInitList.end(); ++itr)
			{
				const TEnumerationType value = *itr;
				Insert(value);
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr void EnumerationSet<TEnumerationType, T>::Remove(TEnumerationType aValue)
		{
			const size_t index = GetIndex(aValue);
			myData.set(index, false);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr void EnumerationSet<TEnumerationType, T>::Clear()
		{
			myData.reset();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TEnumerationType, class T>
		/*inline*/ constexpr void EnumerationSet<TEnumerationType, T>::Invert()
		{
			myData = ~myData;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr bool EnumerationSet<TEnumerationType, T>::Contains(TEnumerationType aValue) const
		{
			const size_t index = GetIndex(aValue);
			return myData[index];
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr size_t EnumerationSet<TEnumerationType, T>::Count() const
		{
			/*
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
			*/

			return myData.count();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr size_t EnumerationSet<TEnumerationType, T>::IsEmpty() const
		{
			return !myData.any();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TEnumerationType, class T>
		/*inline*/ constexpr EnumerationSet<TEnumerationType, T> EnumerationSet<TEnumerationType, T>::Difference(const EnumerationSet<TEnumerationType, T>& aSet) const
		{
			return *this & (~aSet);
		}

		template <typename TEnumerationType, class T>
		/*inline*/ constexpr EnumerationSet<TEnumerationType, T> EnumerationSet<TEnumerationType, T>::Intersection(const EnumerationSet<TEnumerationType, T>& aSet) const
		{
			return *this & aSet;
		}

		template <typename TEnumerationType, class T>
		/*inline*/ constexpr EnumerationSet<TEnumerationType, T> EnumerationSet<TEnumerationType, T>::Union(const EnumerationSet<TEnumerationType, T>& aSet) const
		{
			return *this | aSet;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
#if 0
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr EnumerationSet<TEnumerationType, T>& SetToDifference(const EnumerationSet<TEnumerationType, T>& aSet)
		{
			*this = Difference(aSet);
			return *this;
		}
		
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr EnumerationSet<TEnumerationType, T>& SetToIntersection(const EnumerationSet<TEnumerationType, T>& aSet)
		{
			*this = Intersection(aSet);
			return *this;
		}
		
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr EnumerationSet<TEnumerationType, T>& SetToUnion(const EnumerationSet<TEnumerationType, T>& aSet)
		{
			*this = Union(aSet);
			return *this;
		}
#endif
		
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T, typename... TArgs>
		constexpr EnumerationSet<TEnumerationType, T> Difference(const EnumerationSet<TEnumerationType, T>& aSet, TArgs&&... someArgs)
		{
			return (aSet - ... - someArgs);
		}

		template<typename TEnumerationType, class T, typename... TArgs>
		constexpr EnumerationSet<TEnumerationType, T> Intersection(const EnumerationSet<TEnumerationType, T>& aSet, TArgs&&... someArgs)
		{
			return (aSet & ... & someArgs);
		}

		template<typename TEnumerationType, class T, typename... TArgs>
		constexpr EnumerationSet<TEnumerationType, T> Union(const EnumerationSet<TEnumerationType, T>& aSet, TArgs&&... someArgs)
		{
			return (aSet | ... | someArgs);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr EnumerationSet<TEnumerationType, T> EnumerationSet<TEnumerationType, T>::operator~() const
		{
			EnumerationSet<TEnumerationType, T> result(*this);
			result.myData = ~myData;

			return result;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr EnumerationSet<TEnumerationType, T>& EnumerationSet<TEnumerationType, T>::operator^=(const EnumerationSet<TEnumerationType, T>& aRight)
		{
			myData ^= aRight.myData;
			return *this;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr EnumerationSet<TEnumerationType, T>& EnumerationSet<TEnumerationType, T>::operator-=(const EnumerationSet<TEnumerationType, T>& aRight)
		{
			myData &= ~aRight.myData;
			return *this;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr EnumerationSet<TEnumerationType, T>& EnumerationSet<TEnumerationType, T>::operator|=(const EnumerationSet<TEnumerationType, T>& aRight)
		{
			myData |= aRight.myData;
			return *this;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr EnumerationSet<TEnumerationType, T>& EnumerationSet<TEnumerationType, T>::operator&=(const EnumerationSet<TEnumerationType, T>& aRight)
		{
			myData &= aRight.myData;
			return *this;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr EnumerationSet<TEnumerationType, T>& EnumerationSet<TEnumerationType, T>::operator=(std::initializer_list<TEnumerationType> anInitList)
		{
			Clear();
			Insert(anInitList);

			return *this;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr bool EnumerationSet<TEnumerationType, T>::operator==(const EnumerationSet<TEnumerationType, T>& aRight) const
		{
			return myData == aRight.myData;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr bool EnumerationSet<TEnumerationType, T>::operator!=(const EnumerationSet<TEnumerationType, T>& aRight) const
		{
			return myData != aRight.myData;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TEnumerationType, class T>
		/*inline*/ EnumerationSet<TEnumerationType> operator^(const EnumerationSet<TEnumerationType, T>& aLeft, const EnumerationSet<TEnumerationType, T>& aRight)
		{
			EnumerationSet<TEnumerationType> result = aLeft;
			result ^= aRight;

			return result;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TEnumerationType, class T>
		/*inline*/ EnumerationSet<TEnumerationType, T> operator&(const EnumerationSet<TEnumerationType, T>& aLeft, const EnumerationSet<TEnumerationType, T>& aRight)
		{
			EnumerationSet<TEnumerationType> result = aLeft;
			result &= aRight;

			return result;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TEnumerationType, class T>
		/*inline*/ EnumerationSet<TEnumerationType, T> operator|(const EnumerationSet<TEnumerationType, T>& aLeft, const EnumerationSet<TEnumerationType, T>& aRight)
		{
			EnumerationSet<TEnumerationType> result = aLeft;
			result |= aRight;

			return result;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TEnumerationType, class T>
		/*inline*/ EnumerationSet<TEnumerationType, T> operator-(const EnumerationSet<TEnumerationType, T>& aLeft, const EnumerationSet<TEnumerationType, T>& aRight)
		{
			EnumerationSet<TEnumerationType> result = aLeft;
			result -= aRight;

			return result;
		}

		//=========================================================================================
		// Iterator
		//=========================================================================================
		template<typename TEnumerationType, class T>
		typename EnumerationSet<TEnumerationType, T>::ConstIterator EnumerationSet<TEnumerationType, T>::begin() const
		{
			ConstIterator itr(0, *this);

			static constexpr auto ourStartValue = get_all_enum_values_v<TEnumerationType>[0];
			if (!Contains(ourStartValue))
			{
				itr.Advance();
			}

			return itr;
		}

		template<typename TEnumerationType, class T>
		typename EnumerationSet<TEnumerationType, T>::ConstIterator EnumerationSet<TEnumerationType, T>::end() const
		{
			return ConstIterator(get_enum_entry_count_v<TEnumerationType>, *this);
		}

		template<typename TEnumerationType, class T>
		typename EnumerationSet<TEnumerationType, T>::ConstIterator EnumerationSet<TEnumerationType, T>::cbegin() const
		{
			return begin();
		}

		template<typename TEnumerationType, class T>
		typename EnumerationSet<TEnumerationType, T>::ConstIterator EnumerationSet<TEnumerationType, T>::cend() const
		{
			return end();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ typename EnumerationSet<TEnumerationType, T>::ConstIterator& EnumerationSet<TEnumerationType, T>::ConstIterator::operator++()
		{
			Advance();

			return *this;			
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ typename EnumerationSet<TEnumerationType, T>::ConstIterator EnumerationSet<TEnumerationType, T>::ConstIterator::operator++(int)
		{
			ConstIterator result = *this;
			Advance();

			return result;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ constexpr void typename EnumerationSet<TEnumerationType, T>::ConstIterator::Advance()
		{
			++myIndex;

			// Keep advancing until we find a valid entry, or we hit the end
			while (myIndex < get_enum_entry_count_v<TEnumerationType>)
			{
				if (myCollection->Contains(get_all_enum_values_v<TEnumerationType>[myIndex]))
				{
					return;
				}

				++myIndex;
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ bool EnumerationSet<TEnumerationType, T>::ConstIterator::operator<(const ConstIterator & aRight) const
		{
			return myIndex < aRight.myIndex;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ bool EnumerationSet<TEnumerationType, T>::ConstIterator::operator>(const ConstIterator & aRight) const
		{
			return myIndex > aRight.myIndex;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ bool EnumerationSet<TEnumerationType, T>::ConstIterator::operator<=(const ConstIterator & aRight) const
		{
			return myIndex <= aRight.myIndex;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ bool EnumerationSet<TEnumerationType, T>::ConstIterator::operator>=(const ConstIterator & aRight) const
		{
			return myIndex >= aRight.myIndex;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ bool EnumerationSet<TEnumerationType, T>::ConstIterator::operator==(const ConstIterator & aRight) const
		{
			return myIndex == aRight.myIndex;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ bool EnumerationSet<TEnumerationType, T>::ConstIterator::operator!=(const ConstIterator & aRight) const
		{
			return myIndex != aRight.myIndex;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template<typename TEnumerationType, class T>
		/*inline*/ TEnumerationType EnumerationSet<TEnumerationType, T>::ConstIterator::operator*() const
		{
			return get_all_enum_values_v<TEnumerationType>[myIndex];
		}
}
}