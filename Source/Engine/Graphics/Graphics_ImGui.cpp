#include "Graphics_Precompile.hpp"
#include "Graphics_ImGui.hpp"

#if defined(ALBA_IMGUI_ENABLED)
#	include <imgui.cpp>
#	include <imgui_draw.cpp>
#	include <imgui_demo.cpp>

#	ifdef ALBA_PLATFORM_WINDOWS
#		include <examples/imgui_impl_win32.cpp>
#	endif
#endif