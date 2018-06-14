#pragma once

#include "Graphics_API.hpp"
#include "Graphics_Service.hpp"
#include "Core_Module.hpp"
#include "Core_UniquePtr.hpp"

namespace Alba
{
	namespace Graphics
	{
		class GraphicsService;

		//-----------------------------------------------------------------------------------------
		// Name	: GraphicsModule
		// Desc	: Graphics module
		//-----------------------------------------------------------------------------------------
		class GraphicsModule : public Core::Module<GraphicsModule>
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static const char* GetModuleName() { return "Alba.Graphics"; }

				//=================================================================================
				// Public Methods
				//=================================================================================
				bool				OnLoad(Core::AnyDictionary someLoadParams);
				void				OnUnload();

				GraphicsService&	GetGraphicsServiceMutable();

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				Core::UniquePtr<GraphicsService> myGraphicsService;
		};
	}
}