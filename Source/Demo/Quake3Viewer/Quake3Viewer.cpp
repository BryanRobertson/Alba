#include "Quake3Viewer_Precompile.hpp"
#include "Quake3Viewer.hpp"
#include "Quake3Viewer_Module.hpp"

namespace Alba
{
	namespace Quake3Viewer
	{
		ALBA_QUAKE3VIEWER_API void RegisterModules()
		{
			Quake3ViewerModule::Register();
		}
	}
}