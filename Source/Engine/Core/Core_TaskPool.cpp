#include "Core_Precompile.hpp"
#include "Core_TaskPool.hpp"
#include "Core_Assert.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Size of global task pool
		//-----------------------------------------------------------------------------------------
		namespace TaskPoolDetail
		{
			static constexpr size_t theTaskPoolSize = 4096;
			static constexpr size_t theTaskPoolMask = theTaskPoolSize - 1;

			thread_local Array<TaskPool::TaskStorage, theTaskPoolSize> theTaskPool;

			thread_local uint32	theNextFreeTaskIndex = 0u;
			thread_local uint32 theFrameStartIndex	 = 0u;
			thread_local uint32	theFrameEndIndex	 = 0u;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ void TaskPool::Init()
		{
			using namespace TaskPoolDetail;

			theTaskPool.fill(TaskPool::TaskStorage());
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		#if 0
		/*static*/ void TaskPool::Reset()
		{
			using namespace TaskPoolDetail;

			for (uint32 index = theFrameStartIndex; index != theFrameEndIndex; index = (index + 1) & theTaskPoolMask)
			{
				DeallocateTask(&theTaskPool[index]);
			}

			theFrameStartIndex = theFrameEndIndex = theNextFreeTaskIndex = 0u;
		}
		#endif

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ TaskPool::TaskStorage* TaskPool::AllocateTask()
		{
			using namespace TaskPoolDetail;

			const uint32 index = ++theNextFreeTaskIndex;
			ALBA_ASSERT(index < theTaskPool.size());

			const uint32 aModIndex = (index - 1) & theTaskPoolMask;
			theFrameEndIndex = aModIndex;

			ALBA_ASSERT(theFrameEndIndex != theFrameStartIndex, "Max tasks exceeded! Task pool has wrapped around!");
			return &theTaskPool[aModIndex];
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ void TaskPool::DeallocateTask(TaskStorage* aStorage)
		{
			using namespace TaskPoolDetail;

			ALBA_ASSERT(std::distance(aStorage, &theTaskPool[0]) >= 0 && std::distance(aStorage, &theTaskPool[0]) < theTaskPoolSize);
			(void) aStorage;
		}
	}
}