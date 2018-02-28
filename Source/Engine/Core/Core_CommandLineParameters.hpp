#pragma once

//------------------------------------------------------------------------------------------------
// Name      : Core_CommandLineParameters.hpp
// Desc      : Storage for application command-line parameters
// Author    : Bryan Robertson
// Date      : 2018/02/27
//------------------------------------------------------------------------------------------------

#include "Core_API.hpp"
#include "Core_String.hpp"
#include "Core_Vector.hpp"

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
				explicit CommandLineParameters(const Vector<String>& someParameters);

				//=================================================================================
				// Public Methods
				//=================================================================================
				
			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				
		};
	}
}