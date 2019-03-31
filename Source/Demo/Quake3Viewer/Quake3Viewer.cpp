#include "Quake3Viewer_Precompile.hpp"
#include "Quake3Viewer.hpp"
#include "Quake3Viewer_Module.hpp"

namespace Alba
{
	namespace Quake3Viewer
	{
		void RegisterModules()
		{
			Quake3ViewerModule::Register();
		}
	}
}