#pragma once

#include "Core.hpp"
#include "Graphics_API.hpp"

#define ALBA_IMGUI_ENABLED 1

#if defined(ALBA_IMGUI_ENABLED)
#	define IM_ASSERT(anExpr) ALBA_ASSERT(anExpr)
#	include <imgui.h>
#endif

