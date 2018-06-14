#pragma once

#include "Core_Config.hpp"
#include "Core_Vector.hpp"
#include <EASTL/bonus/ring_buffer.h>
#include <EASTL/bonus/fixed_ring_buffer.h>

namespace Alba
{
	namespace Core
	{
		template <typename TValueType, typename Container = Core::Vector<TValueType>, typename Allocator = typename Container::allocator_type>
		using RingBuffer = eastl::ring_buffer<TValueType, Container, Allocator>;

		template <typename TValueType, size_t TCount>
		using FixedRingBuffer = eastl::fixed_ring_buffer<TValueType, TCount>;
	}
}

