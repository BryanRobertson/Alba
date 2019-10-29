//------------------------------------------------------------------------------------------------
// Name      : Core_SharedPtr.hpp
// Desc      : Shared pointer
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include <EASTL/shared_ptr.h>
#include <memory>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	SharedPtr<T>
		//------------------------------------------------------------------------------------------------
		template <typename TValueType>
		using SharedPtr = eastl::shared_ptr<TValueType>;

		//------------------------------------------------------------------------------------------------
		// Name	:	Core::MakeShared
		//------------------------------------------------------------------------------------------------
		template <typename TValueType, typename... TArgs>
		SharedPtr<TValueType> MakeShared(TArgs&&... args)
		{
			return eastl::make_shared<TValueType, TArgs...>(eastl::forward<TArgs>(args)...);
		}

		//------------------------------------------------------------------------------------------------
		// Name	:	Core::AllocateShared
		//------------------------------------------------------------------------------------------------
		template <typename TValueType, typename TAllocator, typename... TArgs>
		SharedPtr<TValueType> AllocateShared(const TAllocator& allocator, TArgs&&... args)
		{
			return eastl::allocate_shared<TValueType, TAllocator, TArgs...>(eastl::forward<TArgs>(args)...);
		}
	}
}

