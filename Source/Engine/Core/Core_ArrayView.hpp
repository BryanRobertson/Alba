#pragma once

#include "Core.hpp"
#include "Core_Vector.hpp"
#include "Core_Array.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	ArrayView
		// Desc	:	Equivalent of StringView for Vector/FixedVector/etc
		//-----------------------------------------------------------------------------------------
		template <typename TDataType>
		class ArrayView
		{
			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				ArrayView() = default;
				ArrayView(const ArrayView&) = default;
				ArrayView(ArrayView&&) = default;

				explicit ArrayView(TDataType* aData, size_t aCount)
					: myBegin(aBegin)
					, myEnd(std::advance(aBegin, aCount))
				{

				}

				explicit ArrayView(TDataType* aBegin, TDataType& anEnd)
					: myBegin(aBegin)
					, myEnd(anEnd)
				{

				}

				template <size_t TSize>
				explicit ArrayView(Array<TDataType, TSize>& anArray)
				{
					myBegin(&(*anArray.begin()));
					myEnd(&(*anArray.end()));
				}

				template <typename TAllocator>
				explicit ArrayView(Vector<TDataType, TAllocator>& aVector)
				{
					myBegin(&(*aVector.begin()));
					myEnd(&(*aVector.end()));
				}

				template<size_t TCount, OverflowBehavior TOverflowBehavior, typename TOverflowAllocator>
				explicit ArrayView(FixedVector<TDataType, TCount, TOverflowBehavior, TOverflowAllocator>& aVector)
				{
					myBegin(&(*aVector.begin()));
					myEnd(&(*aVector.end()));
				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				size_t size() const
				{
					return std::distance(myBegin, myEnd);
				}

				TDataType* begin()
				{
					return myBegin;
				}

				TDataType* end()
				{
					return myEnd;
				}

				const TDataType* begin() const
				{
					return myBegin;
				}

				const TDataType* end() const
				{
					return myEnd;
				}

				TDataType* data()
				{
					return myBegin;
				}

				const TDataType* data() const
				{
					return myBegin;
				}

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				TDataType* myBegin	= nullptr;
				TDataType* myEnd	= nullptr;
		};
	}
}