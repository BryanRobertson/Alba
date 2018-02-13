//------------------------------------------------------------------------------------------------
// Name      : Core_SharedPtr.hpp
// Desc      : Shared pointer
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/shared_ptr.h>

//------------------------------------------------------------------------------------------------
// Name	:	Core_SharedPtr<T>
//------------------------------------------------------------------------------------------------
template <typename TValueType>
using Core_SharedPtr = eastl::shared_ptr<TValueType>;

//------------------------------------------------------------------------------------------------
// Name	:	Core_MakeShared
//------------------------------------------------------------------------------------------------
template <typename TValueType, typename ...TArgs>
Core_SharedPtr<TValueType> Core_MakeShared(TArgs&& args)
{
	return eastl::make_shared<TValueType, TArgs>(eastl::forward<TArgs>(args)...);
}
//------------------------------------------------------------------------------------------------
// Name	:	Core_AllocateShared
//------------------------------------------------------------------------------------------------
template <typename TValueType, typename TAllocator, typename... TArgs>
Core_SharedPtr<TValueType> Core_AllocateShared(const TAllocator& allocator, TArgs&&... args)
{
	return eastl::allocate_shared<TValueType, TAllocator, eastl::forward<TArgs>(args)...);
}
