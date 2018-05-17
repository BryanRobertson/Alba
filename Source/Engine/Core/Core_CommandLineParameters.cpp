#include "Core_Precompile.hpp"
#include "Core_CommandLineParameters.hpp"
#include "Core_FixedString.hpp"
#include "Core_Pair.hpp"

#include <cctype>


namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		CommandLineParameters::CommandLineParameters()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		CommandLineParameters::CommandLineParameters(int argc, char* argv[])
		{
			Init(argc, argv);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		CommandLineParameters::CommandLineParameters(StringView aCommandLineString)
		{
			Init(aCommandLineString);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		CommandLineParameters::CommandLineParameters(const CommandLineParameters& anOther)
			: myParams(anOther.myParams)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		CommandLineParameters::CommandLineParameters(CommandLineParameters&& anOther)
			: myParams(std::move(anOther.myParams))
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		CommandLineParameters& CommandLineParameters::operator=(const CommandLineParameters& anOther)
		{
			myParams = anOther.myParams;
			return *this;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		CommandLineParameters& CommandLineParameters::operator=(CommandLineParameters&& anOther)
		{
			myParams = std::move(anOther.myParams);
			return *this;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void CommandLineParameters::Init(int argc, char* argv[])
		{
			FixedString<128> commandLineStr;

			// Start from index 1 to skip executable name
			for (int index = 1; index < argc; ++index)
			{
				if (index > 1)
				{
					commandLineStr += " ";
				}

				commandLineStr += argv[index];
			}

			Init(commandLineStr.c_str());
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		class CommandLineParser
		{
		public:

			typedef FixedString<32> TokenString;

			CommandLineParser(const char* aCommandLine)
				: myCommandLineString(aCommandLine)
				, myCurrentChar(aCommandLine)
			{

			}

			//-------------------------------------------------------------------------------------
			// Read param
			//-------------------------------------------------------------------------------------
			bool ParseParam(TokenString& aParamName, TokenString& aParamValue)
			{
				aParamName.clear();
				aParamValue.clear();

				bool isParamValid = GetParamName(aParamName);
				if (!isParamValid)
				{
					return false;
				}

				GetParamValue(aParamValue);

				return true;
			}

		private:

			//-------------------------------------------------------------------------------------
			// Get name of parameter
			//-------------------------------------------------------------------------------------
			bool GetParamName(TokenString& aParamName)
			{
				aParamName.clear();

				SkipToDash();

				// Skip to first '-'
				if (!ReadDash())
				{
					return false;
				}

				SkipWhitespace();

				// Return if current character isn't argument name
				if (!std::isalnum(*myCurrentChar))
				{
					return false;
				}

				//Read until end of token
				Pair<const char*, const char*> token;
				token.first = myCurrentChar;
				do
				{
					token.second = ++myCurrentChar;
				} while (*myCurrentChar != '\0' && std::isalnum(*myCurrentChar));

				aParamName.assign(token.first, token.second);
				return true;
			}

			//-------------------------------------------------------------------------------------
			// Get parameter value
			//-------------------------------------------------------------------------------------
			bool GetParamValue(TokenString& aParamValue)
			{
				aParamValue.clear();

				// Skip whitespace
				SkipWhitespace();

				// Try to read a quoted string first
				if (ReadQuotedString(aParamValue))
				{
					return true;
				}

				// Try to read a parameter without a 
				Pair<const char*, const char*> token = MakePair(myCurrentChar, myCurrentChar);
				while (std::isalnum(*myCurrentChar))
				{
					token.second = ++myCurrentChar;
				}

				if (token.second - token.first > 0)
				{
					aParamValue.assign(token.first, token.second);
				}

				return false;
			}

			//-------------------------------------------------------------------------------------
			// Get quoted string
			//-------------------------------------------------------------------------------------
			bool ReadQuotedString(TokenString& aParamValue)
			{
				if (*myCurrentChar != '\"')
				{
					return false;
				}

				++myCurrentChar;

				Pair<const char*, const char*> token = MakePair(myCurrentChar, myCurrentChar);
				while (*myCurrentChar != '\"' && *myCurrentChar != '\0')
				{
					token.second = ++myCurrentChar;
				}

				aParamValue.assign(token.first, token.second);

				if (*myCurrentChar == '\"')
				{
					++myCurrentChar;
				}

				return true;
			}

			//-------------------------------------------------------------------------------------
			// Get parameter value
			//-------------------------------------------------------------------------------------
			bool ReadDash()
			{
				if (*myCurrentChar != '-')
				{
					return false;
				}

				++myCurrentChar;

				// Skip optional '-'
				if (*myCurrentChar == '-')
				{
					++myCurrentChar;
				}

				return true;
			}

			//-------------------------------------------------------------------------------------
			// Get parameter value
			//-------------------------------------------------------------------------------------
			bool SkipWhitespace()
			{
				while (std::isspace(*myCurrentChar))
				{
					++myCurrentChar;
				}

				return true;
			}

			//-------------------------------------------------------------------------------------
			// Skip to next '-' character
			//-------------------------------------------------------------------------------------
			bool SkipToDash()
			{
				while (*myCurrentChar != '-' && *myCurrentChar != '\0')
				{
					++myCurrentChar;
				}

				return *myCurrentChar == '-';
			}

			const char* myCommandLineString;
			const char* myCurrentChar = nullptr;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void CommandLineParameters::Init(StringView aCommandLineString)
		{
			if (aCommandLineString.size() == 0)
			{
				return;
			}

			CommandLineParser parser(aCommandLineString.begin());

			FixedString<32> tokenName;
			FixedString<32> tokenValue;

			while (parser.ParseParam(tokenName, tokenValue))
			{
				const StringView name(tokenName);
				const NoCaseStringHash32 nameHash(name);

				AddParam(tokenName, tokenValue);
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool CommandLineParameters::IsParamPresent(StringView aParamName) const
		{
			const NoCaseStringHash32 hash(aParamName);

			const auto itr = myParams.find(hash);
			const bool isPresent = itr != myParams.end();

			return isPresent;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void CommandLineParameters::AddParam(StringView aParamName, StringView aParamValue /*= nullptr*/)
		{
			const NoCaseStringHash32 hash(aParamName);

			FixedString<32> paramValue;
			if (aParamValue.size() > 0)
			{
				paramValue.assign(aParamValue.begin(), aParamValue.end());
			}

			AddParam(hash, paramValue);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void CommandLineParameters::AddParam(NoCaseStringHash32 aParamNameId, const FixedString<32>& aParamValue /*= FixedString<32>()*/)
		{
			auto itr = myParams.find(aParamNameId);
			if (itr == myParams.end())
			{
				ParamData paramData;
				paramData.myValue = aParamValue.c_str();

				// If the token is empty then the param is just a boolean switch
				if (aParamValue.empty())
				{
					paramData.myCachedTypedValue = true;
				}
				else
				{
					paramData.myCachedTypedValue.Clear();
				}

				myParams.insert(MakePair(aParamNameId, std::move(paramData)));
			}
			else
			{
				itr->second.myValue = aParamValue.c_str();
				itr->second.myCachedTypedValue.Clear();
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		CommandLineParameters::ParamData* CommandLineParameters::GetParamDataMutable(NoCaseStringHash32 aParamNameId)
		{
			auto itr = myParams.find(aParamNameId);

			return itr != myParams.end()
					? &(itr->second)
					: nullptr;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		const CommandLineParameters::ParamData* CommandLineParameters::GetParamData(NoCaseStringHash32 aParamNameId) const
		{
			auto itr = myParams.find(aParamNameId);

			return itr != myParams.end()
				? &(itr->second)
				: nullptr;
		}
	}
}