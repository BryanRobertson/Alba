#pragma once

#include "Core.hpp"
#include <iostream>

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <size_t TSize>
		class FixedStringStreamBuf : public std::basic_streambuf<char>
		{
			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				FixedStringStreamBuf()
				{
					//myString.resize(TSize);
					myString.assign(TSize, ' ');

					char* begin = myString.begin();
					char* last = myString.begin() + TSize;

					std::basic_streambuf<char>::setp(begin, last);
				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				const FixedString<TSize>& str() const
				{
					return myString;
				}

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				FixedString<TSize> myString;
		};
		
		//-----------------------------------------------------------------------------------------
		// Name	:	Core_FixedStringStream
		// Desc	:	Version of std::stringstream for FixedString
		//-----------------------------------------------------------------------------------------
		template <size_t TSize>
		class FixedStringStream : public std::basic_ostream<char>
		{
			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				FixedStringStream()
					: std::basic_ostream<char>(&myStreamBuffer)
				{

				}

				const FixedString<TSize>& str() const
				{
					return myStreamBuffer.str();
				}

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				FixedStringStreamBuf<TSize>	myStreamBuffer;
		};
	}
}