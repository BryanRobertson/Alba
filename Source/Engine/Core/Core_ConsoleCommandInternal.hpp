#pragma once

#include "Core_API.hpp"
#include "Core_StringView.hpp"
#include "Core_Any.hpp"
#include "Core_StringHash.hpp"
#include "Core_TypeTraits.hpp"

namespace Alba
{
	namespace Core
	{
		namespace ConsoleCommandInternal
		{
			struct ParamTypeVTableBase
			{
				std::tuple<bool, StringView> (*FromStringFunc)(const StringView& aStr, void* aValueOut);
			};

			template <typename TDataType>
			struct ParamTypeVTable : public ParamTypeVTableBase
			{
				//-----------------------------------------------------------------------------------------
				//-----------------------------------------------------------------------------------------
				ParamTypeVTable()
				{
					FromStringFunc = &ConvertFromString;
				}

				//-----------------------------------------------------------------------------------------
				//-----------------------------------------------------------------------------------------
				static bool IsExponentMarker(char aCharacter)
				{
					switch (aCharacter)
					{
						case 'e':
						case 'E':
						case 's':
						case 'S':
						case 'f':
						case 'F':
						case 'd':
						case 'D':
						case 'l':
						case 'L':
							return true;

						default:
							return false;
					}
				}

				//-----------------------------------------------------------------------------------------
				//-----------------------------------------------------------------------------------------
				static std::tuple<bool, StringView> ConvertFromString(StringView aStr, void* aValueOut)
				{
					if (aStr.length() == 0)
					{
						return { false, StringView() };
					}

					//-------------------------------------------------------------------------------------
					// String
					//-------------------------------------------------------------------------------------
					if constexpr (is_string<TDataType>::value)
					{
						size_t begin = 0;
						size_t index = 0;

						// Check for opening quote, if we find one then read until we find a closing quote
						// or the end of input
						if (aStr[begin] == '\"')
						{
							++begin;
							while (index < aStr.length() && aStr[index] != '\"')
							{
								++index;
							}

							// Assign string
							const StringView subStr = aStr.substr(begin, index - begin);
							*static_cast<TDataType*>(aValueOut).assign(subStr.begin(), subStr.end());

							if (index < aStr.length())
							{
								++index;
							}

							return { true, subStr };
						}
						else
						{
							while (index < aStr.length() && !std::isblank(aStr[index]))
							{
								++index;
							}
	
							// Assign string
							const StringView subStr = aStr.substr(begin, index - begin);
							*static_cast<TDataType*>(aValueOut).assign(subStr.begin(), subStr.end());

							return { true, subStr };
						}
					}
					//-------------------------------------------------------------------------------------
					// Integral/Floating point type
					//-------------------------------------------------------------------------------------
					else if constexpr (is_integral<TDataType>::value || is_floating_point<TDataType>::value)
					{
						size_t begin = 0;
						size_t index = 0;

						// Find end of number data
						{
							// Sign
							if (aStr[0] == '-' || aStr[1] == '+')
							{
								++index;
							}

							// Digits
							while (std::isdigit(aStr[index]))
							{
								++index;
							}

							if constexpr (is_floating_point<TDataType>::value)
							{
								// Decimal Point
								if (aStr[index] == '.')
								{
									++index;
								}

								// Digits
								while (std::isdigit(aStr[index]))
								{
									++index;
								}

								// Exponent
								if (IsExponentMarker(aStr[index]))
								{
									++index;

									// Sign
									if (aStr[0] == '-' || aStr[1] == '+')
									{
										++index;
									}

									// Digits
									while (std::isdigit(aStr[index]))
									{
										++index;
									}
								}
							}
						}

						// Convert input string data to integer
						const StringView subStr = aStr.substr(begin, index - begin);
						if ( !StringConverter<TDataType>::FromString(subStr, *static_cast<TDataType*>(aValueOut)) )
						{
							return { false, StringView };
						}

						return { true, subStr };
					}
					//-------------------------------------------------------------------------------------
					// Bool
					//-------------------------------------------------------------------------------------
					else if constexpr (std::is_same<TDataType, bool>::value)
					{
						// Interpret 1 or 0 as boolean
						if ( (aStr[0] == '1' || aStr[0] == '0') && aStr.length() == 1 || std::isblank(aStr[1]))
						{
							*static_cast<TDataType*>(aValueOut) = (aStr[0] == '1');

							return { true, StringView(0, 1) };
						}

						// true
						if (aStr.length() == 4 || aStr.length() > 4 && std::isblank(aStr[4]) )
						{
							if (CaseInsensitiveCompare(aStr.substr(0, 4), "true"_sv) == 0)
							{
								return { true, aStr.substr(0, 4) };
							}
						}

						// false
						if (aStr.length() == 5 || aStr.length() > 5 && std::isblank(aStr[5]))
						{
							if (CaseInsensitiveCompare(aStr.subtr(0, 5), "false"_sv) == 0)
							{
								return { true, aStr.substr(0, 5) };
							}
						}
					}

					return { false, StringView() };
				}
			};

			template <typename TDataType>
			static ParamTypeVTable<TDataType> Get()
			{
				static ParamTypeVTable<TDataType> vtable;
				return vtable;
			}
		}
	}
}