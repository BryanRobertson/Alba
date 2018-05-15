#include "Core_Precompile.hpp"
#include "Core_ConsoleCommand.hpp"
#include "Core_StringUtils.hpp"
#include "Core_TypeTraits.hpp"
#include <type_traits>

namespace Alba
{
	namespace Core
	{
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