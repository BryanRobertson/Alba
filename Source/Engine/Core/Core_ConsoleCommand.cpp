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
			: myName(aName.data(), aName.length())
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
			// Util lambdas
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

			auto locSkipWhitespace = [&itr, &end]()
			{
				while (itr != end && std::isblank(*itr))
				{
					++itr;
				}
			};

			//-------------------------------------------------------------------------------------
			// Skip command name
			//-------------------------------------------------------------------------------------
			locSkipWhitespace();
			if ( !locSkipCommandName(myName.c_str()) )
			{
				return 1;
			}

			//-------------------------------------------------------------------------------------
			// Process arguments
			//-------------------------------------------------------------------------------------
			for (auto& param : myParams)
			{
				locSkipWhitespace();

				bool parseSuccess = false;
				StringView tokenOut;

				const Alba::Core::StringView parseState(itr, std::distance(itr, end));
				std::tie(parseSuccess, tokenOut) = param.myVTable->FromStringFunc(parseState, param.myOutputData);

				if (parseSuccess)
				{
					itr += tokenOut.length();
				}
				else
				{
					return 1;
				}
			}
			
			return 0;
		}
	}
}