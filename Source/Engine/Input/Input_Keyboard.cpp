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
		void Keyboard::UpdateKeyHeldDurations(const Core::Time& aTime)
		{
			for (Key key : myPressedKeys)
			{
				myKeyHeldDurations.erase(key);
			}

			const auto deltaTime = chrono::duration_cast<Core::DurationNanoSeconds>(aTime.GetGameDeltaTime());
			for (auto& itr : myKeyHeldDurations)
			{
				itr.second += deltaTime;
			}
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Core::DurationNanoSeconds Keyboard::GetKeyHeldDuration(Key aKey) const
		{
			using namespace chrono_literals;

			if (auto itr = myKeyHeldDurations.find(aKey); itr != myKeyHeldDurations.end())
			{
				return itr->second;
			}

			return 0ms;
		}
	}
}