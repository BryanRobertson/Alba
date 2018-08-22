#pragma once

#include "Graphics_API.hpp"
#include "Graphics_Shader.hpp"
#include "Core_BasicTypes.hpp"
#include "Core_Assert.hpp"
#include "Math_Vector.hpp"

namespace Alba
{
	namespace Graphics
	{
		struct InitParams;
		using namespace Alba::BasicTypes;

		//-----------------------------------------------------------------------------------------
		// Name	:	RenderBackEnd
		// Desc	:	Base class for renderer implementations using a specific graphics API
		//-----------------------------------------------------------------------------------------
		class ALBA_GRAPHICS_API RenderBackEnd
		{
			public:

				//=================================================================================
				// Public Constructors / Destructors
				//=================================================================================
				RenderBackEnd();
				virtual ~RenderBackEnd();

				//=================================================================================
				// Public Methods
				//=================================================================================
				virtual uint32	Init(const InitParams& someInitParams) = 0;
				virtual void	ClearBuffer(const Math::Vector4f& aColour) = 0;
				virtual void	Present() = 0;
				virtual void	ShutDown() = 0;

				virtual uint32	CreateVertexShaderFromString(ShaderId aShaderId, Core::StringView aString) = 0;
				virtual uint32	CreateVertexShaderFromFile(ShaderId aShaderId, Core::StringView aFileName) = 0;

				virtual uint32	CreatePixelShaderFromString(ShaderId aShaderId, Core::StringView aString) = 0;
				virtual uint32	CreatePixelShaderFromFile(ShaderId aShaderId, Core::StringView aFileName) = 0;
		};
	}
}