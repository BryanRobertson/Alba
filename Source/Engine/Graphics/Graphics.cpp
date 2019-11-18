#include "Graphics_Precompile.hpp"
#include "Graphics.hpp"
#include "Graphics_Module.hpp"
#include "Graphics_ImGuiModule.hpp"
#include "Graphics_ConsoleModule.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void RegisterModules()
		{
			GraphicsModule::Register();
			ImGuiModule::Register();
			ConsoleModule::Register();
		}
	}
}