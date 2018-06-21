#pragma once

//------------------------------------------------------------------------------------------------
// Name      : Core_Algorithm.hpp
// Desc      : STL Algorithm type functions
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------
#include "Core.hpp"
#include <EASTL/algorithm.h>
#include <EASTL/heap.h>
#include <EASTL/sort.h>
#include <algorithm>

namespace Alba
{
	namespace Algorithm
	{
		using eastl::adjacent_find;
		using eastl::all_of;
		using eastl::any_of;
		using eastl::none_of;
		using eastl::min_element;
		using eastl::max_element;
		using eastl::binary_search;
		using eastl::binary_search_i;
		using eastl::change_heap;
		using eastl::copy;
		using eastl::copy_if;
		using eastl::copy_n;
		using eastl::copy_n_impl;
		using eastl::copy_backward;
		using eastl::count;
		using eastl::count_if;
		using eastl::equal;
		using eastl::equal_range;
		using eastl::fill;
		using eastl::fill_n;
		using eastl::find;
		using eastl::find_end;
		using eastl::find_first_not_of;
		using eastl::find_first_of;
		using eastl::find_if;
		using eastl::find_if_not;
		using eastl::find_first_of;
		using eastl::find_first_not_of;
		using eastl::find_last_of;
		using eastl::find_last_not_of;
		using eastl::find_if_not;
		using eastl::for_each;
		using eastl::generate;
		using eastl::generate_n;
		using eastl::identical;
		using eastl::iter_swap;
		using eastl::lexicographical_compare;
		using eastl::lower_bound;
		using eastl::make_heap;
		using eastl::min;
		using eastl::max;
		using eastl::median;
		using eastl::mismatch;
		using eastl::move;
		using eastl::move_backward;
		using eastl::nth_element;
		using eastl::partial_sort;
		using eastl::push_heap;
		using eastl::pop_heap;
		using eastl::random_shuffle;
		using eastl::remove;
		using eastl::remove_if;
		using eastl::remove_copy;
		using eastl::remove_heap;
		using eastl::replace;
		using eastl::replace_if;
		using eastl::replace_copy;
		using eastl::replace_copy_if;
		using eastl::reverse_copy;
		using eastl::reverse;
		using eastl::rotate;
		using eastl::rotate_copy;
		using eastl::search;
		using eastl::search_n;
		using eastl::set_difference;
		using eastl::set_intersection;
		using eastl::set_symmetric_difference;
		using eastl::sort;
		using eastl::sort_heap;
		using eastl::stable_sort;
		using eastl::swap;
		using eastl::transform;
		using eastl::unique;
		using eastl::upper_bound;
		using eastl::is_permutation;
		using eastl::next_permutation;

		using std::includes;
		using std::inplace_merge;
		using std::partial_sort_copy;
		using std::partition;
		using std::prev_permutation;
		using std::search_n;
		using std::set_union;
		using std::stable_partition;
		using std::unique_copy;
	}
}
