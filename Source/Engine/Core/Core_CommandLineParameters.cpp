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
		CommandLineParameters::CommandLineParameters(const char* aCommandLineString)
		{
			Init(aCommandLineString);
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
		void CommandLineParameters::Init(const char* aCommandLineString)
		{
			if (!aCommandLineString)
			{
				return;
			}


			// Parse command line
			enum ParseState
			{
				SkipToParam,
				ReadParamName,
				ReadParamValue
			};

			ParseState state = SkipToParam;

			const char* currentChar = aCommandLineString;

			Pair<const char*, const char*> token = MakePair(aCommandLineString, aCommandLineString);
			FixedString<32> name;

			while (*currentChar != '\0')
			{
				switch (state)
				{
					//--------------------------------------------------------------
					// Skip to next param
					//--------------------------------------------------------------
					case SkipToParam:
					{
						if (*currentChar == '-')
						{
							state = ReadParamName;
							token.first = token.second = currentChar+1;
						}
					}
					break;

					//--------------------------------------------------------------
					// Read Param Name
					//--------------------------------------------------------------
					case ReadParamName:
					{
						if (std::isspace(*currentChar))
						{
							state = ReadParamValue;

							name.clear();
							name.assign(token.first, token.second);

							while (std::isspace(*currentChar))
							{
								++currentChar;
							}
							
							token = MakePair(currentChar, currentChar);
							continue;
						}
						else
						{
							++token.second;
						}
					}
					break;

					//--------------------------------------------------------------
					// Read Param Value
					//--------------------------------------------------------------
					case ReadParamValue:
					{
						if (*currentChar == '-' || (*currentChar == ' ' && *currentChar == '-') )
						{
							state = SkipToParam;

							ParamData paramData;
							paramData.myValue.assign(token.first, token.second);

							// If the token is empty then the param is just a boolean switch
							if (token.first == token.second)
							{
								paramData.myCachedTypedValue = true;
							}

							myParams.push_back(MakePair(StringHash32(name.c_str()), paramData));
							continue;
						}
						else
						{
							++token.second;
						}
					}
					break;
				}

				++currentChar;
			}
		}
	}
}