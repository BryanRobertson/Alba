#pragma once

#include "Graphics_API.hpp"
#include "Core_BasicTypes.hpp"
#include "Core_UniquePtr.hpp"
#include "Core_AnyDictionary.hpp"
#include "Core_ResourceId.hpp"
#include "Math_Vector.hpp"
#include "Graphics_RenderBackEnd.hpp"
#include "Graphics_Shader.hpp"

namespace Alba
{
	namespace Graphics
	{
		struct InitParams;
		class DX11RenderBackEnd;

		typedef RenderBackEnd<DX11RenderBackEnd> RenderBackEndType;

		//-----------------------------------------------------------------------------------------
		// Name	: GraphicsService
		// Desc	: Class that wraps the graphics API
		//-----------------------------------------------------------------------------------------
		class ALBA_GRAPHICS_API GraphicsService final
		{
			public:

				//=================================================================================
				// Public Types
				//=================================================================================
				typedef Core::AnyDictionary AnyDict;

				//=================================================================================
				// Public Constructors/Destructors
				//=================================================================================
				GraphicsService();
				~GraphicsService();

				//=================================================================================
				// Public Methods
				//=================================================================================

				//---------------------------------------------------------------------------------
				// Init/Shutdown
				//---------------------------------------------------------------------------------
				uint32					Init(const InitParams& anInitParams);
				void					ShutDown();

				bool					ImGuiInit();
				void					ImGuiShutDown();

				//---------------------------------------------------------------------------------
				// Frame
				//---------------------------------------------------------------------------------
				void					BeginFrame();
				void					EndFrame();				

				//---------------------------------------------------------------------------------
				// Drawing related
				//---------------------------------------------------------------------------------
				void					ClearBuffer(const Math::Vector4f& aColour);

				//---------------------------------------------------------------------------------
				// Resources
				//---------------------------------------------------------------------------------
				uint32					CreateShaderFromString(Shader& aShader, Core::StringView aString);

				//---------------------------------------------------------------------------------
				// Accessors
				//---------------------------------------------------------------------------------
				inline const AnyDict&	GetPlatformData() const;

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				RenderBackEndType&		GetBackEnd();

				//=================================================================================
				// Private Data
				//=================================================================================
				Core::UniquePtr<RenderBackEndType> myRenderBackEnd;
				Core::AnyDictionary			myPlatformData;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*inline*/ const Core::AnyDictionary& GraphicsService::GetPlatformData() const
		{
			return myPlatformData;
		}
	}
}
