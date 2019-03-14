#pragma once

//------------------------------------------------------------------------------------------------
// Name      : Core_AlignedStorage.hpp
// Desc      : Equivalent to std::aligned_storage
// Author    : Bryan Robertson
// Date      : 2018/02/27
//------------------------------------------------------------------------------------------------
#include "Core.hpp"
#include <EASTL/type_traits.h>

namespace Alba
{
	namespace Core
	{
		template <size_t TSize, size_t TAlign = alignof(uint64)>
		using AlignedStorage = eastl::aligned_storage_t<TSize, TAlign>;

		template <typename TDataType>
		using AlignedStorageT = AlignedStorage<sizeof(TDataType), alignof(TDataType)>;
	}
}