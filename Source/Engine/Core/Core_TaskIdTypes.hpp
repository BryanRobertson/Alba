#pragma once

#include "Core.hpp"
#include "Core_StronglyTypedId.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	TaskThreadId
		// Desc	:	Uniquely identifies a worker thread
		//-----------------------------------------------------------------------------------------
		struct TaskThreadId_Tag
		{
		};

		typedef StronglyTypedId<uint16, TaskThreadId_Tag> TaskThreadId;

		//-----------------------------------------------------------------------------------------
		// Main Thread Id
		//-----------------------------------------------------------------------------------------
		inline constexpr TaskThreadId theMainThreadId(0);

		//-----------------------------------------------------------------------------------------
		// Name	:	TaskThreadId
		// Desc	:	Uniquely identifies a worker thread
		//-----------------------------------------------------------------------------------------
		struct TaskId_Tag
		{
		};

		typedef StronglyTypedId<uint32, TaskId_Tag> TaskId;
	}
}
