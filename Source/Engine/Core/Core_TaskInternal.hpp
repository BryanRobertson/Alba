#pragma once

#include "Core.hpp"
#include "Core_TaskIdTypes.hpp"

namespace Alba
{
	namespace Core
	{
		namespace TaskInternal
		{
			//----------------------------------------------------------------------------------------------
			//----------------------------------------------------------------------------------------------
			inline TaskId CombineTaskId(TaskThreadId aThreadId, uint16 aTaskIndex, uint8 aCounter)
			{
				const uint32 id = (static_cast<uint8>(aThreadId.GetValue()) << 24) | (aTaskIndex << 8) | (aCounter);
				return TaskId(id);
			}

			//----------------------------------------------------------------------------------------------
			//----------------------------------------------------------------------------------------------
			inline TaskThreadId GetThreadId(TaskId aTaskId)
			{
				const uint32 id = aTaskId.GetValue();
				return TaskThreadId(id >> 24);
			}

			//----------------------------------------------------------------------------------------------
			//----------------------------------------------------------------------------------------------
			inline uint16 GetTaskIndex(TaskId aTaskId)
			{
				const uint32 id = aTaskId.GetValue();
				return static_cast<uint16>(id >> 8) & 0xFFFF;
			}

			//----------------------------------------------------------------------------------------------
			//----------------------------------------------------------------------------------------------
			inline uint8 GetCounter(TaskId aTaskId)
			{
				const uint32 id = aTaskId.GetValue();
				return static_cast<uint8>(id & 0xFF);
			}

			//----------------------------------------------------------------------------------------------
			//----------------------------------------------------------------------------------------------
			inline auto SplitTaskId(TaskId aTaskId)
			{
				const uint32 id = aTaskId.GetValue();

				return std::make_tuple
				(
					GetThreadId(aTaskId), GetTaskIndex(aTaskId), GetCounter(aTaskId)
				);
			}
		}
	}
}