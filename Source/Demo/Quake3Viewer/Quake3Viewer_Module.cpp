#include "Quake3Viewer_Precompile.hpp"
#include "Quake3Viewer_Module.hpp"
#include "Core_ConsoleModule.hpp"

namespace Alba
{
	namespace Quake3Viewer
	{
		//------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------
		uint32 TestFunction(int anArg)
		{
			(void)anArg;
			return 1;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Quake3ViewerModule::OnLoad(Core::AnyDictionary /*someLoadParams*/)
		{
			using namespace Alba::StringHashLiterals;

			Core::ConsoleModule& consoleModule = Core::ConsoleModule::Get();
			Core::Console& console = consoleModule.GetConsole();

			console.RegisterCommand("testcommand3"_nocasehash32, [](int aValue1, float aValue2)
			{
				(void)aValue1;
				(void)aValue2;

				return 1u;
			});

			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Quake3ViewerModule::OnUnload()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Quake3ViewerModule::Update(const Core::Time& /*aTime*/)
		{

		}
	}
}