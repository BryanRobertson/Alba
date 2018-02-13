//------------------------------------------------------------------------------------------------
// Name      : Core_UniquePtr.hpp
// Desc      : Unique pointer
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/unique_ptr.h>

//------------------------------------------------------------------------------------------------
// Name	:	Core_UniquePtr<T>
//------------------------------------------------------------------------------------------------
template <typename TValueType>
using Core_UniquePtr = eastl::unique_ptr<TValueType>;

//------------------------------------------------------------------------------------------------
// Name	:	Core_MakeUnique
//------------------------------------------------------------------------------------------------
template <typename TValueType, typename ...TArgs>
Core_UniquePtr<TValueType> Core_MakeUnique(TArgs&& args)
{
	return eastl::make_unique<TValueType, TArgs>(eastl::forward<TArgs>(args)...);
}
//------------------------------------------------------------------------------------------------
// Name	:	Core_AllocateUnique
//------------------------------------------------------------------------------------------------
template <typename TValueType, typename TAllocator, typename... TArgs>
Core_UniquePtr<TValueType> Core_AllocateUnique(const TAllocator& allocator, TArgs&&... args)
{
	return eastl::allocate_unique<TValueType, TAllocator, eastl::forward<TArgs>(args)...);
}
