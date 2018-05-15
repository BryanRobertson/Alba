#pragma once

#include "Core_API.hpp"
#include "Core_StringView.hpp"
#include "Core_Any.hpp"
#include "Core_StringHash.hpp"

namespace Alba
{
	namespace Core
	{
		namespace ConsoleCommandInternal
		{
			struct ParamTypeVTableBase
			{
				size_t(*FromStringFunc)(const StringView& aStr, void* aValueOut);
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
				static size_t ConvertFromString(const StringView& aStr, void* aValueOut)
				{
					if (aStr.length() == 0)
					{
						return 0;
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

							const StringView subStr = aStr.substr(begin, index - begin);

							// Assign string
							*static_cast<TDataType*>(aValueOut).assign(subStr.begin(), subStr.end());

							if (index < aStr.length())
							{
								++index;
							}
						}
						else
						{
							while (index < aStr.length() && std::isblank(aStr[index]))
							{
								++index;
							}

						}

						return index;
					}
					//-------------------------------------------------------------------------------------
					// Integral type
					//-------------------------------------------------------------------------------------
					else if constexpr (std::is_integral<TDataType>::value)
					{
						size_t begin = 0;
						size_t index = 0;

						while (std::isdigit(aStr[index]))
						{
							++index;
						}

						uint64 value = 0;
						uint64 mult = 1;

						for (size_t i = index; index >= begin; --index)
						{
							value += (uint64)(aStr[i] - '0') * mult;
							mult *= 10;
						}

						*static_cast<T*>(aValue) = static_cast<T>(value);

						return index;
					}
					//-------------------------------------------------------------------------------------
					// Floating point
					//-------------------------------------------------------------------------------------
					else if constexpr (std::is_floating_point<TDataType>::value)
					{

					}

					return StringConverter<TDataType>::FromString(aStr, *static_cast<TDataType*>(aValueOut));
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