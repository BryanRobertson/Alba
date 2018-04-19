#include "Gravity_Precompile.hpp"
#include "Gravity_Module.hpp"
#include "Core_ModuleRepository.hpp"
#include "Core_Profile.hpp"

namespace Alba
{
	namespace Gravity
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void RegisterModules()
		{
			GravityModule::Register();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool GravityModule::OnLoad(const Core::AnyDictionary& /*someParameters*/)
		{
			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GravityModule::OnUnload()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GravityModule::Update(const Core::Time& /*aTime*/)
		{
			ALBA_PROFILE_SCOPED(GravityModule_Update);
		}
	}
}