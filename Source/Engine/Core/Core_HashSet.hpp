//------------------------------------------------------------------------------------------------
// Name      : Core_HashSet.hpp
// Desc      : Hash set type
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include <EASTL/hash_set.h>
#include <EASTL/fixed_hash_set.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Core::HashSet<T, Hash, Predicate, Allocator>
		//------------------------------------------------------------------------------------------------
		template <typename TValueType, typename THash = eastl::hash<TValueType>, TPredicate = eastl::equal_to<TValueType>, typename TAllocator = EASTLAllocatorType>
		using HashSet = eastl::hash_set<TValueType, THash, TPredicate, TAllocator>;

		//------------------------------------------------------------------------------------------------
		// Name:	Core::FixedHashSet
		//
		// Template parameters:
		//     TValueType               The type of object the hash_set holds.
		//     TNodeCount				The max number of objects to contain. This value must be >= 1.
		//     TBucketCount				The number of buckets to use. This value must be >= 2.
		//     TEnableOverflow			Whether or not we should use the global heap if our object pool is exhausted.
		//     THashFunc                hash_set hash function. See hash_set.
		//     TPredicateFunc           hash_set equality testing function. See hash_set.
		//------------------------------------------------------------------------------------------------
		template 
		<
			typename TValueType, 
			size_t TNodeCount, 
			size_t TBucketCount = TNodeCount + 1, 
			bool TEnableOverflow = true,
			typename THashFunc = eastl::hash<TValueType>,
			typename PredicateFunc = eastl::equal_to<TValueType>, 
			bool TCacheHashCode = false, 
			typename TOverflowAllocator = EASTLAllocatorType
		>
		using FixedHashSet = eastl::fixed_hash_set
		<
			TValueType, 
			TNodeCount, 
			TBucketCount, 
			TEnableOverflow, 
			THashFunc, 
			TPredicateFunc,
			TCacheHashCode,
			TOverflowAllocator
		>;
	}
}

