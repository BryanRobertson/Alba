//-------------------------------------------------------------------------------------------------
// Name	:	Core_Time.hpp
//-------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include "Core_BasicTypes.hpp"

#pragma warning( push, 3 )  
#include <chrono>
#pragma warning ( pop )

//-------------------------------------------------------------------------------------------------
// Use Core_Chrono instead of std::chrono, 
// so it can be easily switched out for the EASTL version in future if need be
//-------------------------------------------------------------------------------------------------
namespace Core_Chrono			= std::chrono;
namespace Core_ChronoLiterals	= std::chrono_literals;
namespace Core_SI				= std;

using Core_Atto					=  Core_SI::atto;
using Core_Femto				=  Core_SI::femto;
using Core_Pico					=  Core_SI::pico;
using Core_Nano					=  Core_SI::nano;
using Core_Micro				=  Core_SI::micro;
using Core_Milli				=  Core_SI::milli;
using Core_Centi				=  Core_SI::centi;
using Core_Deci					=  Core_SI::deci;
using Core_Deca					=  Core_SI::deca;
using Core_Hecto				=  Core_SI::hecto;
using Core_Kilo					=  Core_SI::kilo;
using Core_Mega					=  Core_SI::mega;
using Core_Giga					=  Core_SI::giga;
using Core_Tera					=  Core_SI::tera;
using Core_Peta					=  Core_SI::peta;
using Core_Exa					=  Core_SI::exa;

typedef Core_Chrono::time_point<Core_Chrono::high_resolution_clock>		Core_TimePoint;
typedef Core_Chrono::duration<uint64, Core_Nano>						Core_TimeDuration;

template <typename TStorageType>
using Core_TimeSeconds = Core_Chrono::duration<TStorageType, Core_SI::ratio<1> >;

//-------------------------------------------------------------------------------------------------
// Name	:	Core_ChronoCast
// Desc	:	Casting functions between different duration types
//-------------------------------------------------------------------------------------------------
template <typename To>
struct Core_ChronoCast_Impl
{
	static To Cast(Core_TimeDuration aDuration)
	{
		return Core_Chrono::duration_cast<To>(aDuration);
	}
};

template <typename To>
To Core_ChronoCast(Core_TimeDuration aDuration)
{
	return Core_ChronoCast_Impl<To>::Cast(aDuration);
}

//-------------------------------------------------------------------------------------------------
// Name	:	Core_Time
// Desc	:	Time related functions
//			e.g. Getting current game time, getting current wall-clock time, etc
//-------------------------------------------------------------------------------------------------
class ALBA_CORE_API Core_Time final
{
	public:

		//=========================================================================================
		// Public Types
		//=========================================================================================
		typedef Core_Chrono::high_resolution_clock		clock_type;

		//=========================================================================================
		// Public Static Methods
		//=========================================================================================
		
		//=========================================================================================
		// Public Constructors
		//=========================================================================================
		Core_Time();

		//=========================================================================================
		// Public Methods
		//=========================================================================================
		void							Reset();
		void							Update();
		void							UpdatePaused();

		//-----------------------------------------------------------------------------------------
		// Wall-clock time (i.e. the real time)
		//-----------------------------------------------------------------------------------------
		Core_TimePoint					GetWallClockTime() const					{ return mySystemTime;  }
		Core_TimeDuration				GetWallClockDeltaTime() const				{ return mySystemTimeDelta; }

		//-----------------------------------------------------------------------------------------
		// Game time (stops when paused)
		//-----------------------------------------------------------------------------------------
		Core_TimePoint					GetGameTime() const							{ return myGameTime;	}
		Core_TimeDuration				GetGameDeltaTime() const					{ return myGameTimeDelta; }

	private:

		//=========================================================================================
		// Private Data
		//=========================================================================================
		Core_TimePoint					mySystemTime;
		Core_TimePoint					myGameTime;

		Core_TimeDuration				mySystemTimeDelta;
		Core_TimeDuration				myGameTimeDelta;
};