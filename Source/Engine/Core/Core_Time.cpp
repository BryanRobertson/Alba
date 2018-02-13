#include "Core_Precompile.hpp"
#include "Core_Time.hpp"

using namespace Core_ChronoLiterals;

///////////////////////////////////////////////////////////////////////////////////////////////////
Core_Time::Core_Time()
{
	Reset();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Core_Time::Reset()
{
	mySystemTime = myGameTime = clock_type::now();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Core_Time::Update()
{
	const Core_TimePoint lastSystemTime = mySystemTime;
	const Core_TimePoint lastGameTime	= myGameTime;

	mySystemTime		= clock_type::now();

	auto timeDelta		= mySystemTime - lastSystemTime;
	myGameTime			= lastGameTime + timeDelta;

	mySystemTimeDelta	= timeDelta;
	myGameTimeDelta		= timeDelta;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Core_Time::UpdatePaused()
{
	const Core_TimePoint lastSystemTime = mySystemTime;
	const Core_TimePoint lastGameTime = myGameTime;

	mySystemTime = clock_type::now();

	auto timeDelta = mySystemTime - lastSystemTime;

	mySystemTimeDelta = timeDelta;
	myGameTimeDelta = 0ns;
}