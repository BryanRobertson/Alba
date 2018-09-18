#pragma once

#include "Core.hpp"
#include "Core_Module.hpp"
#include "Core_CommandLineParameters.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	CommandLineModule
		// Desc	:	Module that encapsulates the commandline parameters for the application
		//-----------------------------------------------------------------------------------------
		class ALBA_CORE_API CommandLineModule final : public Module<CommandLineModule>
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static constexpr StringView GetModuleName() 
				{ 
					return "Alba.Core.CommandLine"; 
				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				void	OnRegister();
				void	OnUnregister();

				bool	OnLoad(Core::AnyDictionary someParameters);
				void	OnUnload();

				const CommandLineParameters& GetParams() const  { return myCommandLineParameters; }
				CommandLineParameters& GetParamsMutable()		{ return myCommandLineParameters; }

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				CommandLineParameters myCommandLineParameters;
		};
	}
}