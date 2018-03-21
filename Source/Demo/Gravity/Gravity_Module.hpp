#pragma once

#include "Gravity_API.hpp"
#include "Core_Module.hpp"

namespace Alba
{
	namespace Gravity
	{
		//-----------------------------------------------------------------------------------------
		// Register modules for this project
		//-----------------------------------------------------------------------------------------
		void ALBA_GRAVITY_API RegisterModules();

		//-----------------------------------------------------------------------------------------
		// Name	:	GravityModule
		//-----------------------------------------------------------------------------------------
		class GravityModule final : public Core::Module<GravityModule>
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static const char* GetModuleName() { return "Alba.Gravity.Gravity"; }

				//=================================================================================
				// Public Methods
				//=================================================================================
				void	OnRegister();
				void	OnUnregister();

				bool	OnLoad(const Core::AnyDictionary& someParameters);
				void	OnUnload();
		};
	}
}