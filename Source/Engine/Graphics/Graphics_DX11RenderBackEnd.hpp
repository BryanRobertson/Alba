#pragma once

#include "Graphics_API.hpp"
#include "Graphics_RenderBackEnd.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	DX11RenderBackEnd
		// Desc	:	Base class for renderer implementations using a specific graphics API
		//-----------------------------------------------------------------------------------------
		class ALBA_GRAPHICS_API DX11RenderBackEnd : public RenderBackEnd
		{
			public:

				//=================================================================================
				// Public Constructors / Destructors
				//=================================================================================
				DX11RenderBackEnd();
				virtual ~DX11RenderBackEnd();

				//=================================================================================
				// Public Methods
				//=================================================================================
				virtual uint32	Init(const InitParams& someInitParams) override;
				virtual void	Present() override;
				virtual void	ShutDown() override;

			private:

				//=================================================================================
				// Private Data
				//=================================================================================

		};
	}
}