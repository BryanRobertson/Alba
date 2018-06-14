#include "Graphics_Precompile.hpp"
#include "Graphics_Module.hpp"
#include "Graphics_Service.hpp"
#include "Core.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool GraphicsModule::OnLoad(Core::AnyDictionary someLoadParams)
		{
			const InitParams& initParams = someLoadParams.Get<InitParams>();

			myGraphicsService.reset(ALBA_NEW(Alba::Core::AllocationType::Renderer, "Renderer") GraphicsService());
			return myGraphicsService->Init(initParams) == 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GraphicsModule::OnUnload()
		{
			myGraphicsService.reset();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		GraphicsService& GraphicsModule::GetGraphicsServiceMutable()
		{
			return *myGraphicsService;
		}
	}
}