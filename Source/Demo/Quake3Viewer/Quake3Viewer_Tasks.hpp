#pragma once

#include "Quake3Viewer_API.hpp"
#include "Core_Time.hpp"

namespace Alba
{
	namespace Quake3Viewer
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	Tasks
		// Desc	:	Contains all the update tasks for the Quake3Viewer application
		//-----------------------------------------------------------------------------------------
		class Tasks final
		{
			public:

				//=================================================================================
				// Public Methods
				//=================================================================================
				void	Update(Core::Time& aTimeDelta);
		};
	}
}