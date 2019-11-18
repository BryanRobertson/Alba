#include "Core_Precompile.hpp"
#include "Core_Time.hpp"
#include "Core_ChronoLiterals.hpp"

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

			mySystemTimeDelta = chrono::duration_cast<DurationNanoSeconds>(timeDelta);
			myGameTimeDelta = chrono::duration_cast<DurationNanoSeconds>(timeDelta);

			++myFrameIndex;
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////
		void Time::UpdatePaused()
		{
			using namespace ChronoLiterals;

			const TimePoint lastSystemTime = mySystemTime;
			const TimePoint lastGameTime = myGameTime;

			mySystemTime = ClockType::now();

			auto timeDelta = mySystemTime - lastSystemTime;

			mySystemTimeDelta = chrono::duration_cast<DurationNanoSeconds>(timeDelta);
			myGameTimeDelta = 0_milliseconds;

			++myFrameIndex;
		}
	}
}

