#pragma once

#include "Core.hpp"
#include "Core_TaskWrapper.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_TaskSystemModule.hpp"
#include "Core_TaskSystem.hpp"
#include "Core_Task.hpp"

namespace Alba
{
	namespace Core
	{
		class Task;

		/*
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TFunctionType, class = enable_if_t<is_invocable_v<void()>> >
		TaskWrapper CreateTask(TFunctionType&& aFunction)
		{
			TaskSystemModule::Get().GetTaskSystemMutable().CreateTask(std::forward<TFunctionType<aFunction));
		}
		&/
	}
}