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

			myRenderBackEnd.reset(ALBA_NEW(Alba::Core::AllocationType::Renderer, "RenderBackEnd") RenderBackEndType());
			return myRenderBackEnd->Init(anInitParams);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GraphicsService::ShutDown()
		{
			myRenderBackEnd->ShutDown();
			myRenderBackEnd.reset();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool GraphicsService::ImGuiInit()
		{
			return myRenderBackEnd->ImGuiInit();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GraphicsService::ImGuiShutDown()
		{
			myRenderBackEnd->ImGuiShutDown();
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

#			if defined(ALBA_IMGUI_ENABLED)
			{
				ImGuiModule& imGuiModule = ImGuiModule::Get();
				if (imGuiModule.IsLoaded())
				{
					imGuiModule.BeginFrame();
				}
			}
#			endif
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void GraphicsService::EndFrame()
		{
			ConsoleModule& consoleModule = ConsoleModule::Get();
			if (consoleModule.IsLoaded())
			{
				consoleModule.Render();
			}

#			if defined(ALBA_IMGUI_ENABLED)
			{
				ImGuiModule& imGuiModule = ImGuiModule::Get();
				if (imGuiModule.IsLoaded())
				{
					imGuiModule.EndFrame();
				}
			}
#			endif

			myRenderBackEnd->EndFrame();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 GraphicsService::CreateShaderFromString(ShaderId aShaderId, ShaderType aShaderType, Core::StringView aString)
		{
			return myRenderBackEnd->CreateShaderFromString(aShaderId, aShaderType, aString);
		}
		
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		RenderBackEndType& GraphicsService::GetBackEnd()
		{
			return *myRenderBackEnd;
		}
	}
}