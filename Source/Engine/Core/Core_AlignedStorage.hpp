#pragma once

//------------------------------------------------------------------------------------------------
// Name      : Core_AlignedStorage.hpp
// Desc      : Equivalent to std::aligned_storage
// Author    : Bryan Robertson
// Date      : 2018/02/27
//------------------------------------------------------------------------------------------------
#include <EASTL/type_traits.h>

namespace Alba
{
	namespace Core
	{
		template <size_t TSize, size_t TAlign = EASTL_ALIGN_OF(double)>
		using AlignedStorage = eastl::aligned_storage_t<TSize, TAlign>;
	}
}