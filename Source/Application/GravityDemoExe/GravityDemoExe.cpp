#include "GravityDemoExe_Precompile.hpp"
#include "GravityDemoExe.hpp"

#include "Core_CommandLineParameters.hpp"
#include "Core_Logging.hpp"
#include "Core_LogCategory.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_PlatformHeader.hpp"
#include "Core_Memory.hpp"
#include "Core_Memory_Impl.hpp"

#include "Framework.hpp"
#include "Framework_ApplicationUtils.hpp"

#include "Gravity_Module.hpp"

ALBA_IMPLEMENT_LOG_CATEGORY(GravityDemo);

namespace
{
	//-------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------
	Alba::Framework::ApplicationUtils::InitParams locGetApplicationInitParams()
	{
		using namespace Alba::Framework;
		using namespace Alba::StringHashLiterals;

		ApplicationUtils::InitParams initParams;
		initParams.myMainApplicationModuleNameId = "Alba.Gravity"_nocasehash32;

		//---------------------------------------------------------------------
		// Register modules callback
		//---------------------------------------------------------------------
		initParams.myRegisterModulesCallback = []()
		{
			Alba::Gravity::RegisterModules();
		};

		return initParams;
	}
}

#if ALBA_PLATFORM_WINDOWS

	//-------------------------------------------------------------------------------------------------
	// WinMain
	//-------------------------------------------------------------------------------------------------
	int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
	{
		using namespace Alba::Framework;
		ApplicationUtils::InitParams initParams = locGetApplicationInitParams();

		return ApplicationUtils::RunApplication(std::move(initParams), hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	}

#else

	//-------------------------------------------------------------------------------------------------
	// Main
	//-------------------------------------------------------------------------------------------------
	int main(int argc, char** argv)
	{
		using namespace Alba::Framework;
		ApplicationUtils::InitParams initParams = locGetApplicationInitParams();

		return ApplicationUtils::RunApplication(std::move(initParams), argc, argv);
	}

#endif