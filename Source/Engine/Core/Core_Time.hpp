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
	//-------------------------------------------------------------------------------------------------
	// Use Alba:chrono instead of std::chrono, 
	// so it can be easily switched out for the EASTL version in future if need be
	//-------------------------------------------------------------------------------------------------
	namespace chrono = std::chrono;
	namespace chrono_literals = std::chrono_literals;

	namespace Core
	{
		
		
		typedef chrono::high_resolution_clock							HighResolutionClock;
		typedef chrono::time_point<chrono::high_resolution_clock>		TimePoint;
		typedef chrono::duration<uint64, std::milli>					TimeDurationMilliSeconds;
		typedef chrono::duration<uint64, std::nano>						TimeDurationNanoSeconds;

		template <typename TStorageType>
		using TimeSeconds = chrono::duration<TStorageType, std::ratio<1> >;

		typedef uint64 FrameIndex;

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
				TimeDurationNanoSeconds		GetWallClockDeltaTime() const				{ return mySystemTimeDelta; }

				//-----------------------------------------------------------------------------------------
				// Game time (stops when paused)
				//-----------------------------------------------------------------------------------------
				TimePoint					GetGameTime() const							{ return myGameTime;	}
				TimeDurationNanoSeconds		GetGameDeltaTime() const					{ return myGameTimeDelta; }

				//-----------------------------------------------------------------------------------------
				// Frame Index
				//-----------------------------------------------------------------------------------------
				FrameIndex					GetFrameIndex() const						{ return myFrameIndex; }

			private:

				//=========================================================================================
				// Private Data
				//=========================================================================================
				TimePoint					mySystemTime;
				TimePoint					myGameTime;

				TimeDurationNanoSeconds		mySystemTimeDelta;
				TimeDurationNanoSeconds		myGameTimeDelta;

				FrameIndex					myFrameIndex;
		};
	}
}