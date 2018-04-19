//------------------------------------------------------------------------------------------------
// Name      : Core_UniquePtr.hpp
// Desc      : Unique pointer
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include <EASTL/unique_ptr.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	UniquePtr<T>
		//------------------------------------------------------------------------------------------------
		template <typename TValueType, typename TDeleter = eastl::default_delete<TValueType> >
		using UniquePtr = eastl::unique_ptr<TValueType>;

		//------------------------------------------------------------------------------------------------
		// Name	:	MakeUnique
		//------------------------------------------------------------------------------------------------
		template <typename TValueType, typename ...TArgs>
		UniquePtr<TValueType> MakeUnique(TArgs&& ...args)
		{
			return eastl::make_unique<TValueType, TArgs>(eastl::forward<TArgs>(args)...);
		}
	}
}
