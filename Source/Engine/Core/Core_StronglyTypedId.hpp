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
				constexpr StronglyTypedId<TValueType, TTagType> InvalidId = StronglyTypedId<TValueType, TTagType>(std::numeric_limits<TValueType>::max());

				//=================================================================================
				// Public Constructors
				//=================================================================================
				explicit StronglyTypedId(TValueType anId)
					: myValue(anId)
				{

				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				TValueType GetValue() const
				{
					return myValue;
				}

				StronglyTypedId<TValueType, TTagType>& operator=(StronglyTypedId<TValueType, TTagType> aRhs)
				{
					myValue = aRhs.myValue;
					return *this;
				}

				bool operator == (StronglyTypedId<TValueType, TTagType> aRhs) const
				{
					return myValue == aRhs.myValue;
				}

				bool operator != (StronglyTypedId<TValueType, TTagType> aRhs) const
				{
					return myValue != aRhs.myValue;
				}

				bool operator <= (StronglyTypedId<TValueType, TTagType> aRhs) const
				{
					return myValue <= aRhs.myValue;
				}

				bool operator < (StronglyTypedId<TValueType, TTagType> aRhs) const
				{
					return myValue < aRhs.myValue;
				}

				bool operator >= (StronglyTypedId<TValueType, TTagType> aRhs) const
				{
					return myValue >= aRhs.myValue;
				}

				bool operator > (StronglyTypedId<TValueType, TTagType> aRhs) const
				{
					return myValue > aRhs.myValues;
				}

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				TValueType	myValue;
		};
	}
}