#pragma once

#include "Graphics_API.hpp"
#include "Core_BasicTypes.hpp"

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
				virtual void	Present() = 0;
				virtual void	ShutDown() = 0;
		};
	}
}