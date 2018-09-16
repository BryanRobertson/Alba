#pragma once

#include "Core.hpp"
#include "Core_StringView.hpp"
#include "Core_Optional.hpp"
#include "Core_TypeTraits.hpp"
#include "Math.hpp"

#include <cctype>

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	ConsoleCommandParser
		// Desc	:	Class to turn a command-line string into a command name and typed arguments
		//-----------------------------------------------------------------------------------------
		class ConsoleCommandParser final
		{
			public:

				//=================================================================================
				// Public Types
				//=================================================================================
				struct ParseState
				{
					explicit ParseState(StringView anInputString)
						: myInputString(anInputString)
					{

					}

					bool IsAtEnd() const
					{
						return myEndIndex == myInputString.length();
					}

					char Peek() const
					{
						ALBA_ASSERT(!IsAtEnd(), "Attempting to read beyond end of input");
						return myInputString[myEndIndex];
					}

					char Read()
					{
						ALBA_ASSERT(!IsAtEnd(), "Attempting to read beyond end of input");
						const char current = myInputString[myEndIndex];
						++myEndIndex;

						return current;
					}

					void Skip()
					{
						ALBA_ASSERT(!IsAtEnd(), "Attempting to read beyond end of input");
						++myEndIndex;
					}

					StringView GetToken() const
					{
						return myInputString.substr(myStartIndex, myEndIndex - myStartIndex);
					}

					StringView GetRemainingInput() const
					{
						return myInputString.substr(myEndIndex, myInputString.length() - myEndIndex);
					}

					void StartNextToken()
					{
						myStartIndex = myEndIndex;
					}

					StringView	myInputString;

					size_t		myStartIndex	= 0;
					size_t		myEndIndex		= 0;
				};

				//=================================================================================
				// Public Methods
				//=================================================================================
				static std::tuple<bool, ParseState> ParseCommandName(ParseState anInputState);
				static std::tuple<bool, ParseState> SkipWhitespace(ParseState anInputState);

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				template <typename TFloatDataType, class=enable_if_t<is_floating_point_v<TFloatDataType>> >
				static inline std::tuple<bool, ParseState> ParseFloat(ParseState anInputState, TFloatDataType& aFloatDataOut)
				{
					ParseState parseState = anInputState;
					if (parseState.IsAtEnd())
					{
						return { false, anInputState };
					}

					aFloatDataOut = TFloatDataType();

					//------------------------------------------------------------------------
					// Read optional sign
					//------------------------------------------------------------------------

					// Note: Using double internally because it gives more accuracy if the string
					//		 contains exponentiation
					double sign = 1.0f;
					{
						if (parseState.Peek() == '-')
						{
							sign = double(-1.0);
							parseState.Skip();
						}
						else if (parseState.Peek() == '+')
						{
							sign = double(1.0);
							parseState.Skip();
						}
					}

					uint64 wholePartDigits = 0;
					bool hasWholePart = false;
					
					double wholePart = double();
					double fractionalPart = double();

					//------------------------------------------------------------------------
					// Read whole part
					//------------------------------------------------------------------------
					while (!parseState.IsAtEnd() && std::isdigit(parseState.Peek()))
					{
						const char digitChar = parseState.Read();

						wholePartDigits *= 10;
						wholePartDigits += static_cast<uint64>(digitChar - '0');

						hasWholePart = true;
					}

					wholePart = double(wholePartDigits);

					//------------------------------------------------------------------------
					// Read decimal point
					//------------------------------------------------------------------------
					if (!parseState.IsAtEnd() && parseState.Peek() == '.')
					{
						//--------------------------------------------------------------------
						// Read fractional part
						//--------------------------------------------------------------------
						parseState.Skip();

						if (!parseState.IsAtEnd() && !std::isdigit(parseState.Peek()) && !hasWholePart)
						{
							// Either whole part or fractional part must be valid
							return { false, anInputState };
						}

						uint64 fractionalPartDigits = 0;
						uint16 fractionalPartInvMultiplier = 1;

						while (!parseState.IsAtEnd() && std::isdigit(parseState.Peek()))
						{
							const char digitChar = parseState.Read();

							fractionalPartDigits *= 10;
							fractionalPartDigits += static_cast<uint64>(digitChar - '0');
							fractionalPartInvMultiplier *= 10;
						}

						fractionalPart = double(fractionalPartDigits)
										/ double(fractionalPartInvMultiplier);
					}
					else if (!hasWholePart)
					{
						// Either whole part or fractional part must be valid
						return { false, anInputState };
					}	

					double exp = 1.0f;
					
					//------------------------------------------------------------------------
					// Read exponent
					//------------------------------------------------------------------------
					if (!parseState.IsAtEnd())
					{
						if (const char input = parseState.Peek(); input == 'e' || input == 'E')
						{
							parseState.Skip();

							bool isNegative = false;
							if (const char signChar = parseState.Peek(); signChar == '-' || signChar == '+')
							{
								isNegative = signChar == '-';
								parseState.Skip();
							}

							if (parseState.IsAtEnd() || !std::isdigit(parseState.Peek()))
							{
								// Missing exponent
								return { false, anInputState };
							}

							uint16 expDigits = 0;
							while (!parseState.IsAtEnd() && std::isdigit(parseState.Peek()))
							{
								const char digitChar = parseState.Read();

								expDigits *= 10;
								expDigits += static_cast<uint64>(digitChar - '0');
							}

							exp *= Math::Pow(10.0, double(isNegative ? -expDigits : expDigits));
						}
					}

					//------------------------------------------------------------------------
					// Fail if there are invalid characters after the digits
					//------------------------------------------------------------------------
					if (!parseState.IsAtEnd() && !std::isblank(parseState.Peek()))
					{
						return { false, anInputState };
					}

					aFloatDataOut = static_cast<float>(sign * (wholePart + fractionalPart) * exp);

					return { true, parseState };
				}

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				template <typename TIntDataType, class = enable_if_t<is_integral_v<TIntDataType>> >
				static inline std::tuple<bool, ParseState> ParseInt(const ParseState anInputState, TIntDataType& anIntDataOut)
				{
					ParseState parseState = anInputState;
					if (parseState.IsAtEnd())
					{
						return { false, anInputState };
					}

					anIntDataOut = 0;

					//------------------------------------------------------------------------
					// Read optional sign
					//------------------------------------------------------------------------
					TIntDataType sign = 1;
					if constexpr (is_signed_v<TIntDataType>)
					{
						if (parseState.Peek() == '-')
						{
							sign = -1;
						}
						else if (parseState.Peek() == '+')
						{
							sign = 1;
						}

						parseState.Skip();
					}

					//------------------------------------------------------------------------
					// Read digits
					//------------------------------------------------------------------------
					if (parseState.IsAtEnd() || !std::isdigit(parseState.Peek()))
					{
						return { false, anInputState };
					}

					TIntDataType digits = 0;
					while (!parseState.IsAtEnd() && std::isdigit(parseState.Peek()))
					{
						const char digitChar = parseState.Read();

						digits *= 10;
						digits += static_cast<TIntDataType>(digitChar - '0');
					}

					digits *= sign;

					//------------------------------------------------------------------------
					// Fail if there are invalid characters after the digits
					//------------------------------------------------------------------------
					if (!parseState.IsAtEnd() && !std::isblank(parseState.Peek()))
					{
						return { false, anInputState };
					}

					anIntDataOut = digits;
					return { true, parseState };
				}

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				template <typename... TArgs>
				static bool ParseArguments(ParseState anInputState, std::tuple<TArgs...>& someArgumentsOut)
				{
					(void)anInputState;
					(void)someArgumentsOut;

					return false;
				}
		};
	}
}