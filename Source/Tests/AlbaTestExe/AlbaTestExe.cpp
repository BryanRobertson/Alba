#include "AlbaTestExe_Precompile.hpp"

#include "Core_CommandLineParameters.hpp"
#include "Core_Logging.hpp"
#include "Core_LogCategory.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_PlatformHeader.hpp"
#include "Core_ModuleRepository.hpp"
#include "Core_CommandLineModule.hpp"
#include "Core_Memory.hpp"
#include "Core_Memory_Impl.hpp"

#include "Framework.hpp"
#include "Framework_ApplicationUtils.hpp"

#include "AlbaTestExe.hpp"
#include "AlbaTest.hpp"

ALBA_IMPLEMENT_LOG_CATEGORY(AlbaTest);

//-------------------------------------------------------------------------------------------------
// Main
//-------------------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	using namespace Alba::Framework;
	using namespace Alba::StringHashLiterals;

	//------------------------------------------------------------------------------
	// Init Log Manager
	//------------------------------------------------------------------------------
	Alba::Core::LogManager::CreateInstance();

	//------------------------------------------------------------------------------
	// Init command line parameters
	//------------------------------------------------------------------------------
	Alba::Core::CommandLineParameters commandLineParameters(argc, argv);

	//------------------------------------------------------------------------------
	// Initialise modules
	//------------------------------------------------------------------------------
	{
		Alba::Core::ModuleRepository::Create();

		{
			Alba::Core::CommandLineModule::Register();
			Alba::Core::ModuleRepository::Get().LoadModule
			(
				"Alba.Core.CommandLine"_nocasehash32,
				std::move(commandLineParameters)
			);
		}
	}

	{
		Alba::Tests::RegisterModules();

		Alba::Core::ModuleRepository& moduleRepository = Alba::Core::ModuleRepository::Get();
		if (!moduleRepository.LoadModule("Alba.Tests.AlbaTest"_nocasehash32))
		{
			using namespace Alba::Tests;
			namespace LogCategories = Alba::Tests::LogCategories;

			ALBA_LOG_INFO(AlbaTest, "Aborting...");
		}
	}

	//------------------------------------------------------------------------------
	// Shutdown module repository
	//------------------------------------------------------------------------------
	Alba::Core::ModuleRepository::Destroy();

	//------------------------------------------------------------------------------
	// Shutdown Log Manager
	//------------------------------------------------------------------------------
	Alba::Core::LogManager::DestroyInstance();
}
