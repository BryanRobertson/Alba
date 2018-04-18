#pragma once

#include "Graphics_API.hpp"

namespace Alba
{
	namespace Graphics
	{
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
				virtual void Present() = 0;
		};
	}
}