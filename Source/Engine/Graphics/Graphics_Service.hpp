#pragma once

#include "Graphics_API.hpp"
#include "Core_BasicTypes.hpp"
#include "Core_UniquePtr.hpp"
#include "Math_Vector.hpp"

namespace Alba
{
	namespace Graphics
	{
		struct InitParams;
		using namespace Alba::BasicTypes;

		class RenderBackEnd;

		//-----------------------------------------------------------------------------------------
		// Name	: GraphicsService
		// Desc	: Class that wraps the graphics API
		//-----------------------------------------------------------------------------------------
		class ALBA_GRAPHICS_API GraphicsService final
		{
			public:

				//=================================================================================
				// Public Constructors/Destructors
				//=================================================================================
				GraphicsService();
				~GraphicsService();

				//=================================================================================
				// Public Methods
				//=================================================================================
				uint32		Init(const InitParams& anInitParams);
				void		ClearBuffer(const Math::Vector4f& aColour);
				void		Present();
				void		ShutDown();

				RenderBackEnd& GetBackEnd();

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				Core::UniquePtr<RenderBackEnd> myRenderBackEnd;
		};
	}
}
