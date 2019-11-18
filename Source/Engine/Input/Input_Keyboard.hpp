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
		class Keyboard final
		{
			public:

				friend class InputService;

				//=================================================================================
				// Public Constructors
				//=================================================================================
				Keyboard();

				//=================================================================================
				// Public Methods
				//=================================================================================
				void					UpdateKeyHeldDurations(const Core::Time& aTime);

				inline bool				IsKeyHeld(Key aKey) const;
				inline bool				IsKeyUp(Key aKey) const;

				inline const KeySet&	GetHeldKeys() const;
				inline KeySet			GetUpKeys() const;
				inline const KeySet&	GetPressedKeys() const;

				inline KeySet&			GetHeldKeysMutable();
				inline KeySet&			GetPressedKeysMutable();

				Core::DurationNanoSeconds GetKeyHeldDuration(Key aKey) const;

			private:

				//=================================================================================
				// Private Data
				//=================================================================================

				// Keys that are Held this frame
				KeySet				myHeldKeys;

				// Keys that were just released this frame
				KeySet				myPressedKeys;

				// For each held key, how long the key has been held for
				Core::VectorMap<Key, Core::DurationNanoSeconds> myKeyHeldDurations;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Keyboard::IsKeyHeld(Key aKey) const
		{
			return myHeldKeys.Contains(aKey);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool Keyboard::IsKeyUp(Key aKey) const
		{
			return !myHeldKeys.Contains(aKey);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		const KeySet& Keyboard::GetHeldKeys() const
		{
			return myHeldKeys;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		KeySet Keyboard::GetUpKeys() const
		{
			return ~myHeldKeys;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		const KeySet& Keyboard::GetPressedKeys() const
		{
			return myPressedKeys;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		KeySet& Keyboard::GetHeldKeysMutable()
		{
			return myHeldKeys;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		KeySet& Keyboard::GetPressedKeysMutable()
		{
			return myPressedKeys;
		}

	}
}