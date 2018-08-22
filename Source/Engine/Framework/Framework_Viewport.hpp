#pragma once

#include "Framework_RenderCallback.hpp"

namespace Alba
{
	namespace Framework
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	Viewport
		// Desc	:	Represents a renderable region of the window
		//			with a custom render callback
		//-----------------------------------------------------------------------------------------
		class Viewport final
		{
			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				inline Viewport(ViewportId anId, RenderCallback aCallback);

				//=================================================================================
				// Public Methods
				//=================================================================================
				inline ViewportId		GetId() const;
				inline RenderCallback	GetRenderCallback() const;

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				ViewportId				myViewportId;
				RenderCallback			myRenderCallback;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Viewport::Viewport(ViewportId anId, RenderCallback aCallback)
			: myViewportId(anId)
			, myRenderCallback(aCallback)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*inline*/ ViewportId Viewport::GetId() const
		{
			return myViewportId;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*inline*/ RenderCallback Viewport::GetRenderCallback() const
		{
			return myRenderCallback;
		}
	}
}