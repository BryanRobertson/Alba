#pragma once

#include <atomic>

struct Core_ThreadEvent
{
	void Signal()		{}
	bool WaitAndReset() {}
};

int Core_AtomicIncrement(int value)
{

}

//std::atomic_thread_fence(std::memory_order_acquire)
//std::atomic_thread_fence(std::memory_order_release)

//std::atomic<int> a;
//a.store(1, std::memory_order_relaxed)
//