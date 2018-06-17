#include "Core_Precompile.hpp"
#include "Core_CommandLineParameters.hpp"
#include "Core_FixedString.hpp"
#include "Core_Pair.hpp"
#include "Core_Optional.hpp"

#include <cctype>


namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		#if defined(ALBA_PLATFORM_WINDOWS) && defined(ALBA_COMPILER_VISUALSTUDIO)
			/*static*/ CommandLineParameters CommandLineParameters::CreateWindows()
			{
				CommandLineParameters params;

				const int argc = __argc;
				char** argv = __argv;

				params.Init(argc, argv);

				return params;
			}
		#endif

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		CommandLineParameters::CommandLineParameters()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		CommandLineParameters::CommandLineParameters(int argc, char** argv)
		{
			Init(argc, argv);
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
		void CommandLineParameters::Init(int argc, char** argv)
		{
			// Only used for arguments that span
			FixedString<256> tempArgBuffer;

			for (size_t index = 1; index < argc; ++index)
			{
				StringView arg = argv[index];
				
				// Skip to first argument
				while (index < argc && argv[index][0] != '-')
				{
					arg = argv[index];
					++index;
				}

				// If we didn't get an argument then we're done
				if (index >= argc)
				{
					break;
				}

				StringView paramName = StringView(argv[index]);
				const size_t startIndex = paramName.find_first_not_of('-', 0);

				if (startIndex == StringView::npos)
				{
					continue;
				}

				paramName.remove_prefix(startIndex);

				// Read argument value, if the argument only takes up one entry in argv, then we'll use stringview
				// otherwise construct a temporary argument buffer
				size_t count = 0;
				for (size_t searchIndex = index+1; searchIndex < argc && argv[searchIndex][0] != '-'; ++searchIndex, ++count)
				{

				}

				const NoCaseStringHash32 paramNameId(paramName);
				if (count == 0)
				{
					AddParam(paramNameId);
				}
				else if (count == 1)
				{
					const StringView value = StringView(argv[index + 1]);

					AddParam(paramNameId, value);
					++index;
				}
				else
				{
					tempArgBuffer.clear();
					for (size_t offset = 1; offset <= count; ++offset)
					{
						if (offset > 1)
						{
							tempArgBuffer.append(" ");
						}

						tempArgBuffer.append(argv[index + offset]);
					}

					String value(tempArgBuffer.begin(), tempArgBuffer.end());

					AddParam(paramNameId, std::move(value));
					index += count;
				}
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
		void CommandLineParameters::AddParam(NoCaseStringHash32 aParamNameId, String aParamValue /*= ""*/)
		{
			myStringStorage.push_back(std::move(aParamValue));
			AddParam(aParamNameId, StringView(aParamValue));
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void CommandLineParameters::AddParam(NoCaseStringHash32 aParamNameId, StringView aParamValue /*= ""*/)
		{
			auto itr = myParams.find(aParamNameId);
			if (itr == myParams.end())
			{
				ParamData paramData;
				paramData.myValue = aParamValue.data();

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
				itr->second.myValue = aParamValue.data();
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