//-------------------------------------------------------------------------------------------------
// Name	:	Time.hpp
//-------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include "Core_BasicTypes.hpp"

#pragma warning( push, 3 )  
#include <chrono>
#pragma warning ( pop )

namespace Alba
{
	namespace Core
	{
		//-------------------------------------------------------------------------------------------------
		// Use Core::Chrono instead of std::chrono, 
		// so it can be easily switched out for the EASTL version in future if need be
		//-------------------------------------------------------------------------------------------------
		namespace Chrono			= std::chrono;
		namespace ChronoLiterals	= std::chrono_literals;
		namespace SI				= std;

		using Atto					=  SI::atto;
		using Femto					=  SI::femto;
		using Pico					=  SI::pico;
		using Nano					=  SI::nano;
		using Micro					=  SI::micro;
		using Milli					=  SI::milli;
		using Centi					=  SI::centi;
		using Deci					=  SI::deci;
		using Deca					=  SI::deca;
		using Hecto					=  SI::hecto;
		using Kilo					=  SI::kilo;
		using Mega					=  SI::mega;
		using Giga					=  SI::giga;
		using Tera					=  SI::tera;
		using Peta					=  SI::peta;
		using Exa					=  SI::exa;

		typedef Chrono::high_resolution_clock							HighResolutionClock;
		typedef Chrono::time_point<Chrono::high_resolution_clock>		TimePoint;
		typedef Chrono::duration<uint64, Nano>							TimeDuration;

		template <typename TStorageType>
		using TimeSeconds = Chrono::duration<TStorageType, SI::ratio<1> >;

		//-------------------------------------------------------------------------------------------------
		// Name	:	Core::ChronoCast
		// Desc	:	Casting functions between different duration types
		//-------------------------------------------------------------------------------------------------
		template <typename To>
		struct ChronoCast_Impl
		{
			static constexpr To Cast(TimeDuration aDuration)
			{
				return Chrono::duration_cast<To>(aDuration);
			}
		};

		template <typename To>
		constexpr To ChronoCast(TimeDuration aDuration)
		{
			return ChronoCast_Impl<To>::Cast(aDuration);
		}

		//-------------------------------------------------------------------------------------------------
		// Name	:	Core::Time
		// Desc	:	Time related functions
		//			e.g. Getting current game time, getting current wall-clock time, etc
		//-------------------------------------------------------------------------------------------------
		class ALBA_CORE_API Time final
		{
			public:

				//=========================================================================================
				// Public Types
				//=========================================================================================
				typedef HighResolutionClock	ClockType;

				//=========================================================================================
				// Public Static Methods
				//=========================================================================================
		
				//=========================================================================================
				// Public Constructors
				//=========================================================================================
				Time();

				//=========================================================================================
				// Public Methods
				//=========================================================================================
				void						Reset();
				void						Update();
				void						UpdatePaused();

				//-----------------------------------------------------------------------------------------
				// Wall-clock time (i.e. the real time)
				//-----------------------------------------------------------------------------------------
				TimePoint					GetWallClockTime() const					{ return mySystemTime;  }
				TimeDuration				GetWallClockDeltaTime() const				{ return mySystemTimeDelta; }

				//-----------------------------------------------------------------------------------------
				// Game time (stops when paused)
				//-----------------------------------------------------------------------------------------
				TimePoint					GetGameTime() const							{ return myGameTime;	}
				TimeDuration				GetGameDeltaTime() const					{ return myGameTimeDelta; }

			private:

				//=========================================================================================
				// Private Data
				//=========================================================================================
				TimePoint					mySystemTime;
				TimePoint					myGameTime;

				TimeDuration				mySystemTimeDelta;
				TimeDuration				myGameTimeDelta;
		};
	}
}