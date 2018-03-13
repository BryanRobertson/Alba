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
				// Public Constructors
				//=================================================================================
				explicit CommandLineParameters();
				explicit CommandLineParameters(int argc, char* argv[]);
				explicit CommandLineParameters(const char* aCommandLineString);

				CommandLineParameters(const CommandLineParameters& anOther);
				CommandLineParameters(CommandLineParameters&& anOther);

				//=================================================================================
				// Public Methods
				//=================================================================================

				//---------------------------------------------------------------------------------
				// Name	:	Init
				// Desc	:	Initialise the command line parameters from command-line data
				//---------------------------------------------------------------------------------
				void Init(int argc, char* argv[]);
				void Init(const char* aCommandLineStr);

				//---------------------------------------------------------------------------------
				// Name	:	IsParamPresent
				// Desc	:	Return true if the specified named argument exists
				//			(This will also return true for binary switches --dosomething)
				//---------------------------------------------------------------------------------
				bool IsParamPresent(const char* aParamName);

				//---------------------------------------------------------------------------------
				// Name	:	TryGetParamValue
				// Desc	:	Try to get named parameter value from the commandline
				//---------------------------------------------------------------------------------
				template <typename TDataType>
				bool TryGetParamValue(const char* aParamName, TDataType& anOutValue)
				{
					const NoCaseStringHash32 paramNameId(aParamName);
					if (ParamData* paramData = GetParamDataMutable(paramNameId) )
					{
						return paramData->GetData(anOutValue);
					}

					return false;
				}

				template <typename TDataType>
				bool TryGetParamValue(NoCaseStringHash32 aParamNameId, TDataType& anOutValue)
				{
					if (ParamData* paramData = GetParamDataMutable(aParamNameId))
					{
						return paramData->GetData(anOutValue);
					}

					return false;
				}

				//---------------------------------------------------------------------------------
				// Name	: AddParam
				// Desc : Add a parameter
				//---------------------------------------------------------------------------------
				void AddParam(const char* aParamName, const char* aParamValue = nullptr);
				void AddParam(NoCaseStringHash32 aParamNameId, const FixedString<32>& aParamValue = FixedString<32>());

				//---------------------------------------------------------------------------------
				// Operator overloads
				//---------------------------------------------------------------------------------
				CommandLineParameters& operator=(const CommandLineParameters& anOther);
				CommandLineParameters& operator=(CommandLineParameters&& anOther);

			private:

				//=================================================================================
				// Private Types
				//=================================================================================
				struct ParamData
				{	
					FixedString<16> myValue;
					Any				myCachedTypedValue;

					template <typename TDataType>
					bool GetData(TDataType& anOutValue,
								 typename std::enable_if<is_string<TDataType>::value, TDataType>::type* = nullptr)
					{
						anOutValue = myValue.c_str();
						return true;
					}

					template <typename TDataType>
					bool GetData(TDataType& anOutValue,
		 						 typename std::enable_if<!is_string<TDataType>::value, TDataType>::type* = nullptr)
					{
						// Try to get cached converted value first
						if (myCachedTypedValue.Is<TDataType>())
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

						return false;
					}
				};

				typedef VectorMap<NoCaseStringHash32, ParamData> ParamDataCollection;

				//=================================================================================
				// Private Methods
				//=================================================================================
				ParamData* GetParamDataMutable(NoCaseStringHash32 aParamNameId);

				//=================================================================================
				// Private Data
				//=================================================================================
				ParamDataCollection myParams;
		};
	}
}