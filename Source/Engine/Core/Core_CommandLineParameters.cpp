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
				params.Init(__argc, __argv);

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
			Optional<StringView> paramName;
			for (int index = 0; index < argc; ++index)
			{
				const StringView arg = argv[index];
			
				if (!paramName.has_value())
				{
					paramName = Core::StringView(argv[index]);

					if (index + 1 >= argc)
					{
						const NoCaseStringHash32 nameId(argv[index]);
						AddParam(nameId);
					}
				}
				
				const NoCaseStringHash32 nameId(argv[index]);
				const Core::StringView value(argv[index]);

				AddParam(nameId, value);
				paramName.reset();
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void CommandLineParameters::Init(const Core::Vector<String> someParams)
		{
			
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