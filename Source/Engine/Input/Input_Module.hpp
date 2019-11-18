#pragma once

#include "Core.hpp"
#include "Core_Module.hpp"
#include "Core_Array.hpp"
#include "Input_API.hpp"
#include "Input_Service.hpp"

namespace Alba
{
	namespace Input
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		class InputModule : public Core::Module< InputModule>
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static constexpr Core::StringView GetModuleName()
				{
					return "Alba.Input";
				}

				static constexpr auto GetDependencies()
				{
					using namespace Alba::StringHashLiterals;
					return Core::Array<Core::NoCaseStringHash32, 1>
					{{
						"Alba.Core.Window"_nocasehash32
					}};
				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				bool						OnLoad(Core::AnyDictionary someLoadParams);
				void						OnUnload();

				inline InputService&		GetInputServiceMutable();
				inline const InputService&	GetInputService() const;

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				InputService				myInputService;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		InputService& InputModule::GetInputServiceMutable()
		{
			ALBA_ASSERT(IsLoaded());
			return myInputService;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		const InputService& InputModule::GetInputService() const
		{
			ALBA_ASSERT(IsLoaded());
			return myInputService;
		}
	}
}