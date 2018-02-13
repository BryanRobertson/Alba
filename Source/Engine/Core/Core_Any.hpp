//------------------------------------------------------------------------------------------------
// Name      : Core_Any.hpp
// Desc      : Variant type
// Author    : Bryan Robertson
// Date      : 2016/12/20
//------------------------------------------------------------------------------------------------

#pragma once

#include "Core_API.hpp"
#include <EASTL/any.h>

//------------------------------------------------------------------------------------------------
// Name	:	Core_HashMap<Key, Value, Hash, Predicate, Allocator>
//------------------------------------------------------------------------------------------------
typedef eastl::any Core_Any;
