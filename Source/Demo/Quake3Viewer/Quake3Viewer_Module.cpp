#include "Quake3Viewer_Precompile.hpp"
#include "Quake3Viewer_Module.hpp"
#include "Core_ConsoleModule.hpp"

namespace Alba
{
	namespace Quake3Viewer
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Quake3ViewerModule::OnLoad(Core::AnyDictionary /*someLoadParams*/)
		{
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