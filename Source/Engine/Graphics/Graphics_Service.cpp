#include "Graphics_Precompile.hpp"
#include "Graphics_InitParams.hpp"
#include "Graphics_Service.hpp"
#include "Graphics_ImGuiModule.hpp"
#include "Graphics_ConsoleModule.hpp"
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
			myPlatformData = anInitParams.myPlatformData;

			myRenderBackEnd.reset(ALBA_NEW(Alba::Core::AllocationType::Renderer, "RenderBackEnd") DX11RenderBackEnd());
			return myRenderBackEnd->Init(anInitParams);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GraphicsService::ClearBuffer(const Math::Vector4f& aColour)
		{
			myRenderBackEnd->ClearBuffer(aColour);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GraphicsService::BeginFrame()
		{
			myRenderBackEnd->BeginFrame();

			ImGuiModule imGuiModule = ImGuiModule::Get();
			if (imGuiModule.IsLoaded())
			{
				imGuiModule.BeginFrame();
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GraphicsService::EndFrame()
		{
			ConsoleModule consoleModule = ConsoleModule::Get();
			if (consoleModule.IsLoaded())
			{
				consoleModule.Render();
			}

			ImGuiModule imGuiModule = ImGuiModule::Get();
			if (imGuiModule.IsLoaded())
			{
				imGuiModule.EndFrame();
			}

			myRenderBackEnd->EndFrame();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		RenderBackEnd& GraphicsService::GetBackEnd()
		{
			return *myRenderBackEnd;
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