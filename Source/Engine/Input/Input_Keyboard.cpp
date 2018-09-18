#include "Input_Precompile.hpp"
#include "Input_Keyboard.hpp"
#include "Core_Time.hpp"

namespace Alba
{
	namespace Input
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Keyboard::Keyboard()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Keyboard::Update(const Core::Time& /*aTime*/, KeySet somePressedKeys, KeySet someReleasedKeys)
		{
			myPressedKeys = somePressedKeys;
			myReleasedKeys = someReleasedKeys;

			for (Key key : someReleasedKeys)
			{
				myKeyHeldDurations.erase(key);
			}
		}
	}
}