#pragma once

#include "Core.hpp"
#include "Core_Module.hpp"
#include "Core_LogCategory.hpp"

namespace Alba
{
	namespace Tests
	{
		ALBA_DECLARE_LOG_CATEGORY(AlbaTest);

		//-----------------------------------------------------------------------------------------
		// Name	:	AlbaTestModule
		// Desc	:	Alba test module
		//-----------------------------------------------------------------------------------------
		class AlbaTestModule : public Core::Module<AlbaTestModule>
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static const char* GetModuleName() { return "Alba.Tests.AlbaTest"; }

				//=================================================================================
				// Public Methods
				//=================================================================================
				bool	OnLoad(Core::AnyDictionary someParameters);
				void	OnUnload();
		};
	}
}