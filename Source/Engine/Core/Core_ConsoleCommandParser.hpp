#pragma once

#include "Core.hpp"
#include "Core_StringView.hpp"
#include "Core_Optional.hpp"
#include "Core_TypeTraits.hpp"
#include "Math.hpp"

#include <cctype>
#include <tuple>

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TArgType>
		struct console_argument_parse_traits
		{
			static constexpr bool is_valid = false;
			//static bool Parse(ConsoleCommandParser::ParseState& aParseState, TArgType& anArgOutput);
		};

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
				// Parse a floating point value
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
						int16 fractionalPartNumDigits = 0;

						while (!parseState.IsAtEnd() && std::isdigit(parseState.Peek()))
						{
							const char digitChar = parseState.Read();

							fractionalPartDigits *= 10;
							fractionalPartDigits += static_cast<uint64>(digitChar - '0');

							++fractionalPartNumDigits;
						}

						const double invMultiplier = Math::Pow(10.0, -fractionalPartNumDigits);
						const double multiplier = Math::Pow(10.0, fractionalPartNumDigits);

						fractionalPart = double(fractionalPartDigits) * invMultiplier;
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

					parseState.StartNextToken();

					return { true, parseState };
				}

				//---------------------------------------------------------------------------------
				// Parse an integer value
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
					parseState.StartNextToken();

					return { true, parseState };
				}

				//---------------------------------------------------------------------------------
				// Parse a string value
				//---------------------------------------------------------------------------------
				static inline std::tuple<bool, ParseState> ParseString(const ParseState anInputState, StringView& aStringDataOut)
				{
					// StringView version just returns a substring from the original command string that was parsed in
					// (which is safe because the string is guaranteed be valid at the point where the command is executed)
					auto [skipped, parseState] = SkipWhitespace(anInputState);

					if (parseState.IsAtEnd())
					{
						return { false, anInputState };
					}

					Optional<char> quoteCharacter;
					if (const char inputChar = parseState.Peek(); (inputChar == '\'' || inputChar == '\"') )
					{
						quoteCharacter = inputChar;

						parseState.Skip();
						parseState.StartNextToken();
					}

					// Scan until we hit the end of input
					// or we hit a closing quote (if we found an opening quote)
					while (!parseState.IsAtEnd() )
					{
						const char current = parseState.Peek();
						if (quoteCharacter.has_value())
						{
							if (current == quoteCharacter.value())
							{
								break;
							}							
						}
						else if (std::isblank(current))
						{
							break;
						}

						parseState.Read();
					}

					// Get the token value
					aStringDataOut = parseState.GetToken();

					// Skip the closing quote
					if (quoteCharacter.has_value() && !parseState.IsAtEnd())
					{
						parseState.Skip();
					}

					parseState.StartNextToken();

					return { true, parseState };
				}

				template <typename TStringDataType, class = enable_if_t<is_string_v<TStringDataType>> >
				static inline std::tuple<bool, ParseState> ParseString(const ParseState anInputState, TStringDataType& aStringDataOut)
				{
					StringView aStringView;
					auto [success, outputState] = ParseString(anInputState, aStringView);

					if (success)
					{
						aStringDataOut.reserve(aStringView.length());
						aStringDataOut.assign(aStringView.begin(), aStringView.end());
					}

					return { success, outputState };
				}

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				template <typename... TArgs>
				static bool ParseArguments(ParseState anInputState, std::tuple<TArgs...>& someArgumentsOut)
				{
					// Basically what this does, is for each entry in the tuple, call "ParseArgument"
					// in turn for each element (passing in the tuple as a reference)
					//
					// If this call completes successfully then the tuple will contain the parsed argument values
					return std::apply
					(
						[&anInputState](auto&&... someArgs)
						{
							return (ParseArgument(anInputState, someArgs) && ...);
						}, 
						std::forward<std::tuple<TArgs...>>(someArgumentsOut)
					);
				}

			private:

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				template <typename TArgType>
				static bool ParseArgument(ParseState& anInputState, TArgType&& anArgument)
				{
					using ArgValueType = std::remove_reference_t<TArgType>;

					auto [skippedWhitespace, state] = SkipWhitespace(anInputState);

					// Integral
					if constexpr (is_integral_v<ArgValueType>)
					{
						auto[success, parseState] = ParseInt(state, anArgument);
						if (success)
						{
							anInputState = parseState;
							return true;
						}
					}
					// Floating point
					else if constexpr (is_floating_point_v<ArgValueType>)
					{
						auto[success, parseState] = ParseFloat(state, anArgument);
						if (success)
						{
							anInputState = parseState;
							return true;
						}
					}
					// String, FixedString or StringView
					else if constexpr (is_string_v<ArgValueType> || is_same_v<ArgValueType, StringView>)
					{
						auto[success, parseState] = ParseString(state, anArgument);
						if (success)
						{
							anInputState = parseState;
							return true;
						}
					}
					// Custom parser
					else if constexpr (console_argument_parse_traits<ArgValueType>::is_valid)
					{
						return console_argument_parse_traits::Parse(state, anArgument);
					}
					else
					{
						(void)anArgument;
						static_assert(false, "This type is not supported by the console parser: Specialise console_argument_parse_traits for your type to provide a parsing function");
					}

					return false;
				}
		};
	}
}