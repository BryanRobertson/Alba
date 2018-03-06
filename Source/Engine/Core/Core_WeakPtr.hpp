//------------------------------------------------------------------------------------------------
// Name      : Core_WeakPtr.hpp
// Desc      : Weak pointer
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core.hpp"
#include <EASTL/shared_ptr.h>

namespace Alba
{
	namespace Core
	{
		//------------------------------------------------------------------------------------------------
		// Name	:	Core::WeakPtr<T>
		//------------------------------------------------------------------------------------------------
		template <typename TValueType>
		using WeakPtr = eastl::weak_ptr<TValueType>;
	}
}

