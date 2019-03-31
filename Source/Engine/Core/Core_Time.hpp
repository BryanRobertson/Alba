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

	namespace Core
	{		
		using HighResolutionClock	= chrono::high_resolution_clock;
		using TimePoint				= chrono::time_point<chrono::high_resolution_clock>;

		template <typename TUnits, typename TRatio>
		using Duration = chrono::duration<TUnits, TRatio>;

		using DurationMilliSeconds	=	Duration<uint64, std::milli>;
		using DurationNanoSeconds	=	Duration<uint64, std::nano>;
		using DurationSeconds		=	Duration<float, std::ratio<1> >;

		using FrameIndex = uint64;

		//-------------------------------------------------------------------------------------------------
		// Name	:	Core::Time
		// Desc	:	Time related functions
		//			e.g. Getting current game time, getting current wall-clock time, etc
		//-------------------------------------------------------------------------------------------------
		class Time final
		{
			public:

				//=========================================================================================
				// Public Types
				//=========================================================================================
				using ClockType = HighResolutionClock;

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
				DurationNanoSeconds			GetWallClockDeltaTime() const				{ return mySystemTimeDelta; }

				//-----------------------------------------------------------------------------------------
				// Game time (stops when paused)
				//-----------------------------------------------------------------------------------------
				TimePoint					GetGameTime() const							{ return myGameTime;	}
				DurationNanoSeconds			GetGameDeltaTime() const					{ return myGameTimeDelta; }

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

				DurationNanoSeconds			mySystemTimeDelta;
				DurationNanoSeconds			myGameTimeDelta;

				FrameIndex					myFrameIndex;
		};
	}
}