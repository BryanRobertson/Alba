#pragma once

#include "Core.hpp"
#include "Core_VectorMap.hpp"
#include "Core_Time.hpp"

#include "Input_KeyboardEnumerations.hpp"

namespace Alba
{
	namespace Input
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	Keyboard
		// Desc	:	Wraps a keyboard input device
		//-----------------------------------------------------------------------------------------
		class Keyboard final
		{
			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				Keyboard();

				//=================================================================================
				// Public Methods
				//=================================================================================
				inline bool		IsKeyHeld(Key aKey) const;
				inline bool		IsKeyReleased(Key aKey) const;

			private:

				//=================================================================================
				// Private Data
				//=================================================================================

				// Keys that are down this frame
				KeySet				myPressedKeys;

				// Keys that were just released this frame
				KeySet				myReleasedKeys;

				// For each key that's currently held, how long has it been held for?
				Core::VectorMap<Key, Core::TimeDurationMilliSeconds> myKeyHeldDurations;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Keyboard::IsKeyHeld(Key aKey) const
		{
			return myPressedKeys.Contains(aKey);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Keyboard::IsKeyReleased(Key aKey) const
		{
			return myReleasedKeys.Contains(aKey);
		}
	}
}