#pragma once

#include "Core.hpp"
#include "Core_TypeTraits.hpp"
#include <limits>

#undef max

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name : StronglyTypedId
		// Desc : Strongly typed integer ID type. Can only be assigned to from another ID of the
		//		  same type, which ensures ID types can never get mixed up
		//-----------------------------------------------------------------------------------------
		template <typename TValueType, typename TTagType>
		class StronglyTypedId
		{
			public:

				static_assert(is_integral_v<TValueType>, "Strongly typed ID must be an integral type!");

				//=================================================================================
				// Public Constants
				//=================================================================================
				static const StronglyTypedId InvalidId;

				//=================================================================================
				// Public Constructors
				//=================================================================================
				constexpr StronglyTypedId()
					: myValue(InvalidId.myValue)
				{

				}

				explicit constexpr StronglyTypedId(TValueType anId)
					: myValue(anId)
				{

				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				constexpr TValueType GetValue() const
				{
					return myValue;
				}

				bool IsValid() const
				{
					return myValue != InvalidId.GetValue();
				}

				constexpr StronglyTypedId<TValueType, TTagType>& operator=(StronglyTypedId<TValueType, TTagType> aRhs)
				{
					myValue = aRhs.myValue;
					return *this;
				}

				constexpr bool operator == (StronglyTypedId<TValueType, TTagType> aRhs) const
				{
					return myValue == aRhs.myValue;
				}

				constexpr bool operator != (StronglyTypedId<TValueType, TTagType> aRhs) const
				{
					return myValue != aRhs.myValue;
				}

				constexpr bool operator <= (StronglyTypedId<TValueType, TTagType> aRhs) const
				{
					return myValue <= aRhs.myValue;
				}

				constexpr bool operator < (StronglyTypedId<TValueType, TTagType> aRhs) const
				{
					return myValue < aRhs.myValue;
				}

				constexpr bool operator >= (StronglyTypedId<TValueType, TTagType> aRhs) const
				{
					return myValue >= aRhs.myValue;
				}

				constexpr bool operator > (StronglyTypedId<TValueType, TTagType> aRhs) const
				{
					return myValue > aRhs.myValues;
				}

				void Invalidate()
				{
					myValue = InvalidId;
				}

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				TValueType	myValue;
		};

		template <typename TValueType, typename TTagType>
		/*static*/ const StronglyTypedId<TValueType, TTagType> StronglyTypedId<TValueType, TTagType>::InvalidId (std::numeric_limits<TValueType>::max());
	}
}