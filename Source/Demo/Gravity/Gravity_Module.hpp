#pragma once

#include "Gravity_API.hpp"
#include "Core_Module.hpp"

namespace Alba
{
	namespace Gravity
	{
		enum class GravityModuleState : uint8;

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
				static const char* GetModuleName() { return "Alba.Gravity"; }

				//=================================================================================
				// Public Constructors
				//=================================================================================
				GravityModule();

				//=================================================================================
				// Public Methods
				//=================================================================================
				bool	OnLoad(const Core::AnyDictionary& someParameters);
				void	OnUnload();

				void	Update(const Core::Time& aTime);

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				GravityModuleState	myGravityModuleState;
		};
	}
}