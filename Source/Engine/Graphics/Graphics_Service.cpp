#include "Graphics_Precompile.hpp"
#include "Graphics_InitParams.hpp"
#include "Graphics_Service.hpp"
#include "Graphics_DX11RenderBackEnd.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		GraphicsService::GraphicsService()
		{
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		GraphicsService::~GraphicsService()
		{
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 GraphicsService::Init(const InitParams& anInitParams)
		{
			myRenderBackEnd.reset(ALBA_NEW(Alba::Core::AllocationType::Renderer, "RenderBackEnd") DX11RenderBackEnd());
			return myRenderBackEnd->Init(anInitParams);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GraphicsService::ClearBuffer()
		{
			myRenderBackEnd->ClearBuffer();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GraphicsService::Present()
		{
			myRenderBackEnd->Present();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GraphicsService::ShutDown()
		{
			myRenderBackEnd->ShutDown();
			myRenderBackEnd.reset();
		}
	}
}