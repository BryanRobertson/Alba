#pragma once

#include "Core_StringHash.hpp"
#include "Framework_API.hpp"

//-----------------------------------------------------------------------------------------
// Provides a default application implementation
//-----------------------------------------------------------------------------------------
namespace Alba
{
	namespace Framework
	{
		struct ApplicationInitParams;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		namespace ApplicationUtils
		{
			typedef void(*RegisterModulesCallback)();
			typedef void(*SetupApplicationInitParamsCallback)(Alba::Framework::ApplicationInitParams& someInitParams);

			//-----------------------------------------------------------------------------------------
			//-----------------------------------------------------------------------------------------
			struct ALBA_FRAMEWORK_API InitParams
			{
				// NameId of the main module of the application
				Core::NoCaseStringHash32			myMainApplicationModuleNameId;

				// Optional callback for a function to register additional modules on startup
				RegisterModulesCallback				myRegisterModulesCallback = nullptr;

				// Optional callback to set initial application init params
				SetupApplicationInitParamsCallback	mySetupInitParamsCallback = nullptr;
			};

			//-----------------------------------------------------------------------------------------
			//-----------------------------------------------------------------------------------------
			extern ALBA_FRAMEWORK_API uint32 RunApplication(InitParams&& someInitParams);
		}
	}
}