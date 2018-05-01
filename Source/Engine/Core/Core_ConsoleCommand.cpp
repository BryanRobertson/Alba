#include "Core_Precompile.hpp"
#include "Core_ConsoleCommand.hpp"
#include "Core_StringUtils.hpp"
#include "Core_TypeTraits.hpp"
#include <type_traits>

namespace Alba
{
	namespace Core
	{
		namespace ConsoleInternal
		{ 
			template <typename TDataType>
			struct ParamTypeVTable : public ConsoleCommand::ParamTypeVTableBase
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

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		ConsoleCommand::ConsoleCommand(const StringView& aName)
			: myName(aName.data(), myName.length())
			, myNameId()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		ConsoleCommand::~ConsoleCommand()
		{

		}

		//-----------------------------------------------------------------------------------------
		// Name	:	ConsoleCommand::Execute
		// Desc	:	Execute a command from user input
		//-----------------------------------------------------------------------------------------
		uint32 ConsoleCommand::Execute(const StringView& aCommandString)
		{
			StringView::const_iterator itr = aCommandString.begin();
			const StringView::const_iterator end = aCommandString.end();

			//-------------------------------------------------------------------------------------
			// Skip command name
			//-------------------------------------------------------------------------------------
			auto locSkipCommandName = [&itr, &end](const StringView& aCommandName) -> bool
			{
				if (std::size_t(std::distance(itr, end)) < aCommandName.length())
				{
					return false;
				}

				for (char character : aCommandName)
				{
					if (itr == end || character != *itr)
					{
						return false;
					}
				}

				return true;
			};

			//-------------------------------------------------------------------------------------
			// Skip whitespace
			//-------------------------------------------------------------------------------------
			auto locSkipWhitespace = [&itr, &end]()
			{
				while (itr != end && std::isblank(*itr))
				{
					++itr;
				}
			};

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------

			return false;
		}
	}
}