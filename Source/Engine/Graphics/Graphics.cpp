#include "Graphics_Precompile.hpp"
#include "Graphics.hpp"
#include "Graphics_Module.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ALBA_GRAPHICS_API RegisterModules()
		{
			GraphicsModule::Register();
		}
	}
}