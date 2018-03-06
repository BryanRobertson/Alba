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
		namespace chrono			= std::chrono;
		namespace chrono_literals	= std::chrono_literals;
		
		typedef chrono::high_resolution_clock							HighResolutionClock;
		typedef chrono::time_point<chrono::high_resolution_clock>		TimePoint;
		typedef chrono::duration<uint64, std::nano>						TimeDuration;

		template <typename TStorageType>
		using TimeSeconds = chrono::duration<TStorageType, std::ratio<1> >;

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