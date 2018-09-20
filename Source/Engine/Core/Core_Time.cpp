#include "Core_Precompile.hpp"
#include "Core_Time.hpp"

namespace Alba
{
	namespace Core
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////
		Time::Time()
		{
			Reset();
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////
		void Time::Reset()
		{
			mySystemTime = myGameTime = ClockType::now();
			myFrameIndex = 0;
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////
		void Time::Update()
		{
			const TimePoint lastSystemTime = mySystemTime;
			const TimePoint lastGameTime = myGameTime;

			mySystemTime = ClockType::now();

			auto timeDelta = mySystemTime - lastSystemTime;
			myGameTime = lastGameTime + timeDelta;

			mySystemTimeDelta = chrono::duration_cast<TimeDurationNanoSeconds>(timeDelta);
			myGameTimeDelta = chrono::duration_cast<TimeDurationNanoSeconds>(timeDelta);

			++myFrameIndex;
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////
		void Time::UpdatePaused()
		{
			using namespace std::chrono_literals;

			const TimePoint lastSystemTime = mySystemTime;
			const TimePoint lastGameTime = myGameTime;

			mySystemTime = ClockType::now();

			auto timeDelta = mySystemTime - lastSystemTime;

			mySystemTimeDelta = chrono::duration_cast<TimeDurationNanoSeconds>(timeDelta);
			myGameTimeDelta = 0ms;

			++myFrameIndex;
		}
	}
}

