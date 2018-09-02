#pragma once

//------------------------------------------------------------------------------------------------
// Name      : Core_CommandLineParameters.hpp
// Desc      : Storage for application command-line parameters
// Author    : Bryan Robertson
// Date      : 2018/02/27
//------------------------------------------------------------------------------------------------

#include "Core.hpp"
#include "Core_Any.hpp"
#include "Core_String.hpp"
#include "Core_StringView.hpp"
#include "Core_StringHash.hpp"
#include "Core_StringUtils.hpp"
#include "Core_FixedString.hpp"
#include "Core_Vector.hpp"
#include "Core_VectorMap.hpp"
#include "Core_TypeTraits.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	CommandLineParameters
		// Desc	:	Class to store commandline parameters for the application
		//			Not thread safe, the assumption is that this will be set at application startup
		//			and not modified after that
		//-----------------------------------------------------------------------------------------
		class CommandLineParameters final
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				#if defined(ALBA_PLATFORM_WINDOWS) && defined(ALBA_COMPILER_VISUALSTUDIO)
					static CommandLineParameters CreateWindows();
				#endif

				//=================================================================================
				// Public Constructors
				//=================================================================================
				explicit CommandLineParameters();
				explicit CommandLineParameters(int argc, char** argv);

				CommandLineParameters(const CommandLineParameters& anOther);
				CommandLineParameters(CommandLineParameters&& anOther);

				//=================================================================================
				// Public Methods
				//=================================================================================

				//---------------------------------------------------------------------------------
				// Name	:	Init
				// Desc	:	Initialise the command line parameters from command-line data
				//---------------------------------------------------------------------------------
				void Init(int argc, char** argv);

				//---------------------------------------------------------------------------------
				// Name	:	IsParamPresent
				// Desc	:	Return true if the specified named argument exists
				//			(This will also return true for binary switches --dosomething)
				//---------------------------------------------------------------------------------
				bool IsParamPresent(StringView aParamName) const;

				//---------------------------------------------------------------------------------
				// Name	:	TryGetParamValue
				// Desc	:	Try to get named parameter value from the commandline
				//---------------------------------------------------------------------------------
				template <typename TDataType>
				bool TryGetParamValue(NoCaseStringHash32 aParamNameId, TDataType& anOutValue) const
				{
					if (const ParamData* paramData = GetParamData(aParamNameId))
					{
						return paramData->GetData(anOutValue);
					}

					return false;
				}

				template <typename TDataType>
				bool TryGetParamValue(NoCaseStringHash32 aParamNameId, TDataType& anOutValue, const TDataType& aDefault) const
				{
					if (const ParamData* paramData = GetParamData(aParamNameId))
					{
						return paramData->GetData(anOutValue);
					}

					anOutValue = aDefault;
					return false;
				}

				//---------------------------------------------------------------------------------
				// Name	: AddParam
				// Desc : Add a parameter
				//---------------------------------------------------------------------------------
				void AddParam(NoCaseStringHash32 aParamNameId, StringView aParamValue = "");
				void AddParam(NoCaseStringHash32 aParamNameId, String aParamValue);

				//---------------------------------------------------------------------------------
				// Operator overloads
				//---------------------------------------------------------------------------------
				CommandLineParameters& operator=(const CommandLineParameters& anOther);
				CommandLineParameters& operator=(CommandLineParameters&& anOther);

				//---------------------------------------------------------------------------------
				// Iterators
				//---------------------------------------------------------------------------------
				template <typename TIterator>
				void ForEach_Param(const TIterator& anIterator)
				{
					for (const auto& param : myParams)
					{
						anIterator(param.first, param.second.myValue);
					}
				}

			private:

				//=================================================================================
				// Private Types
				//=================================================================================
				struct ParamData
				{	
					StringView		myValue;
					mutable Any		myCachedTypedValue;

					template <typename TDataType>
					bool GetData(TDataType& anOutValue) const
					{
						if constexpr(is_string_v<TDataType>)
						{
							anOutValue = myValue.data();
							return true;
						}
						else
						{
							// Try to get cached converted value first
							if (myCachedTypedValue.IsSet() && myCachedTypedValue.Is<TDataType>())
							{
								anOutValue = myCachedTypedValue.To<TDataType>();
								return true;
							}
							// Otherwise attempt to convert it
							else if (StringConverter<TDataType>::From(myValue, anOutValue))
							{
								// If the cached value isn't already set, then cache it for future use
								if (!myCachedTypedValue.IsSet())
								{
									myCachedTypedValue.Set(TDataType(anOutValue));
								}

								return true;
							}
						}


						return false;
					}
				};

				typedef VectorMap<NoCaseStringHash32, ParamData> ParamDataCollection;

				//=================================================================================
				// Private Methods
				//=================================================================================
				ParamData* GetParamDataMutable(NoCaseStringHash32 aParamNameId);
				const ParamData* GetParamData(NoCaseStringHash32 aParamNameId) const;

				//=================================================================================
				// Private Data
				//=================================================================================
				ParamDataCollection		myParams;
				Vector<String>			myStringStorage;
		};
	}
}