#pragma once

#include <atomic>

namespace Alba
{
	namespace Core
	{
		//-------------------------------------------------------------------------------------------------
		// Name	:	Core::Atomic
		// Desc :	Alias for std::atomic
		//-------------------------------------------------------------------------------------------------
		template <typename TValueType>
		using Atomic = std::atomic<TValueType>;

		//-------------------------------------------------------------------------------------------------
		// Name	:	Core::AtomicFlag
		// Desc :	Alias for std::atomic_flag
		//-------------------------------------------------------------------------------------------------
		using AtomicFlag = std::atomic_flag;
	}
}