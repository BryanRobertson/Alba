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

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	Class to store commandline parameters for the application
		// Desc	:	
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
				// Name	:	TryGetParamValue
				// Desc	:	Try to get named parameter value from the commandline
				//---------------------------------------------------------------------------------
				template <typename TDataType>
				bool TryGetParamValue(const char* aParamName, TDataType& anOutValue)
				{
					return TryGetParamValue<TDataType>(StringHash32(aParamName));
				}

				template <typename TDataType>
				bool TryGetParamValue(StringHash32 aParamName, TDataType& anOutValue)
				{
					auto itr = myParams.find(aParamName);
					if (itr != myParams.end() && itr->second.myCachedTypedValue.Is<TDataType>())
					{
						anOutValue = itr->second.myCachedTypedValue.To<TDataType>();
						return true;
					}
					else if ( StringConverter<TDataType>::Convert(itr->second.myValue, anOutValue) )
					{
						itr->second.myCachedTypedValue = anOutValue;
						return true;
					}

					return false;
				}

			private:

				//=================================================================================
				// Private Types
				//=================================================================================
				struct ParamData
				{	
					FixedString<16> myValue;
					Any				myCachedTypedValue;
				};

				typedef VectorMap<StringHash32, ParamData> ParamDataCollection;

				//=================================================================================
				// Private Data
				//=================================================================================
				ParamDataCollection myParams;
		};
	}
}