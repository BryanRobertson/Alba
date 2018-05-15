#pragma once

#include "Quake3Viewer_API.hpp"
#include "Core_Module.hpp"


namespace Alba
{
	namespace Quake3Viewer
	{
		//-----------------------------------------------------------------------------------------
		// Name	: Quake3ViewerModule
		// Desc	: Quake3 map viewer module
		//-----------------------------------------------------------------------------------------
		class Quake3ViewerModule : public Core::Module<Quake3ViewerModule>
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static const char* GetModuleName() { return "Alba.Quake3Viewer"; }

				//=================================================================================
				// Public Methods
				//=================================================================================
				bool	OnLoad(const Core::AnyDictionary& someLoadParams);
				void	OnUnload();
				void	Update(const Core::Time& aTime);

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
		};
	}
}