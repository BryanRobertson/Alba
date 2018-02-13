//------------------------------------------------------------------------------------------------
// Name      : Core_Deque.hpp
// Desc      : STL Deque equivalent
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/deque.h>

//------------------------------------------------------------------------------------------------
// Name	:	Core_Deque<T, Allocator>
//------------------------------------------------------------------------------------------------
template <typename TValueType, typename TAllocator = EASTLAllocatorDefault>
using Core_Deque = eastl::deque<TValueType, TAllocator>;

//------------------------------------------------------------------------------------------------
// Name	:	Core_Deque_Sized<T, Size, Allocator>
// Desc	:	Deque with internal subarray size specified
//------------------------------------------------------------------------------------------------
template <typename TValueType, unsigned int kSubarraySize, typename TAllocator = EASTLAllocatorDefault>
using Core_Deque_Sized = eastl::deque<TValueType, TAllocator, kSubarraySize>;
