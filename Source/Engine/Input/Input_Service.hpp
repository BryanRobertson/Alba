#pragma once

#include "Input_API.hpp"
#include "Core_AnyDictionary.hpp"

namespace Alba
{
	namespace Input
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	InputService
		// Desc	:	Provides access to input devices, and updates their state every frame
		//-----------------------------------------------------------------------------------------
		class ALBA_INPUT_API InputService final
		{
			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				InputService();
				~InputService();

				//=================================================================================
				// Public Methods
				//=================================================================================
				uint32	Init(const Core::AnyDictionary& someParams);
				void	ShutDown();

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
		};
	}
}