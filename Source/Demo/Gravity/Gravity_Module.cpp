#include "Gravity_Precompile.hpp"
#include "Gravity_Module.hpp"
#include "Core_ModuleRepository.hpp"
#include "Core_Profile.hpp"

namespace Alba
{
	namespace Gravity
	{
		enum class GravityModuleState : uint8
		{
			Init,
			Loading,
			Running,
			Unloaded
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void RegisterModules()
		{
			GravityModule::Register();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		GravityModule::GravityModule()
		{
			myGravityModuleState = GravityModuleState::Init;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool GravityModule::OnLoad(const Core::AnyDictionary& /*someParameters*/)
		{
			myGravityModuleState = GravityModuleState::Loading;

			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GravityModule::OnUnload()
		{
			myGravityModuleState = GravityModuleState::Unloaded;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GravityModule::Update(const Core::Time& /*aTime*/)
		{
			ALBA_PROFILE_SCOPED(GravityModule_Update);
		}
	}
}