#pragma once

#include "Core.hpp"
#include "Core_TypeTraits.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name : StronglyTypedId
		// Desc : Strongly typed integer ID type. Can only be assigned to from another ID of the
		//		  same type, which ensures ID types can never get mixed up
		//-----------------------------------------------------------------------------------------
		template <typename TValueType, typename TTagType, class = enable_if<is_integral_v<TValueType> > >
		class StronglyTypedId
		{
			public:

				//=================================================================================
				// Public Constants
				//=================================================================================
				static const StronglyTypedId<TValueType, TTagType> InvalidId;

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
					return myValue != InvalidId;
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

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				TValueType	myValue;
		};

		template <typename TValueType, typename TTagType, class _>
		const StronglyTypedId<TValueType, TTagType, _> StronglyTypedId<TValueType, TTagType, _>::InvalidId(std::numeric_limits<TValueType>::max());
	}
}