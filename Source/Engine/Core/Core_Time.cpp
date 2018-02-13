#include "Core_Precompile.hpp"
#include "Core_Time.hpp"

namespace Alba
{
	namespace Core
	{
		using namespace ChronoLiterals;

		///////////////////////////////////////////////////////////////////////////////////////////////////
		Time::Time()
		{
			Reset();
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////
		void Time::Reset()
		{
			mySystemTime = myGameTime = clock_type::now();
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////
		void Time::Update()
		{
			const TimePoint lastSystemTime = mySystemTime;
			const TimePoint lastGameTime = myGameTime;

			mySystemTime = clock_type::now();

			auto timeDelta = mySystemTime - lastSystemTime;
			myGameTime = lastGameTime + timeDelta;

			mySystemTimeDelta = timeDelta;
			myGameTimeDelta = timeDelta;
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////
		void Time::UpdatePaused()
		{
			const TimePoint lastSystemTime = mySystemTime;
			const TimePoint lastGameTime = myGameTime;

			mySystemTime = clock_type::now();

			auto timeDelta = mySystemTime - lastSystemTime;

			mySystemTimeDelta = timeDelta;
			myGameTimeDelta = 0ns;
		}
	}
}

