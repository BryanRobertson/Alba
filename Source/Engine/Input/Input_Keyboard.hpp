#pragma once

#include "Core.hpp"
#include "Core_VectorMap.hpp"
#include "Core_Time.hpp"

#include "Input_API.hpp"
#include "Input_KeyboardEnumerations.hpp"

namespace Alba
{
	namespace Core
	{
		class Time;
	}

	namespace Input
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	Keyboard
		// Desc	:	Wraps a keyboard input device
		//-----------------------------------------------------------------------------------------
		class ALBA_INPUT_API Keyboard final
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

				inline const KeySet& GetPressedKeys() const;
				inline const KeySet& GetReleasedKeys() const;

				void			Update(const Core::Time& aTime, KeySet somePressedKeys, KeySet someReleasedKeys);

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

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		const KeySet& Keyboard::GetPressedKeys() const
		{
			return myPressedKeys;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		const KeySet& Keyboard::GetReleasedKeys() const
		{
			return myReleasedKeys;
		}
	}
}