#pragma once

#include "Graphics_API.hpp"
#include "Core_BasicTypes.hpp"

namespace Alba
{
	namespace Graphics
	{
		struct InitParams;
		using namespace Alba::BasicTypes;

		class GraphicsImplementation;

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
				uint32		Init(InitParams&& anInitParams);
				uint32		ShutDown();

			private:

				//=================================================================================
				// Public Methods
				//=================================================================================
				GraphicsImplementation* myImpl;
		};
	}
}
