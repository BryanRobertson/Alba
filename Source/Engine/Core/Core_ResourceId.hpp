#pragma once

#include "Core.hpp"
#include "Core_StronglyTypedId.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename TResourceType>
		using ResourceId = StronglyTypedId<uint64, TResourceType>;
	}
}