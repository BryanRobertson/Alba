#pragma once

#include "Core.hpp"
#include "Core_Module.hpp"
#include "Input_API.hpp"

namespace Alba
{
	namespace Input
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		class ALBA_INPUT_API InputModule : public Core::Module< InputModule>
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static constexpr Core::StringView GetModuleName()
				{
					return "Alba.Input";
				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				bool					OnLoad(Core::AnyDictionary someLoadParams);
				void					OnUnload();
		};
	}
}