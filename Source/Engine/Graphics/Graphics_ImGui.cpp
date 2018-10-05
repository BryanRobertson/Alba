#include "Graphics_Precompile.hpp"
#include "Graphics_ImGui.hpp"

#if defined(ALBA_IMGUI_ENABLED)

#	pragma warning( push ) 
#	pragma warning( disable : 4390 ) //  empty controlled statement found; is this the intent?

#	include <imgui.cpp>
#	include <imgui_draw.cpp>
#	include <imgui_demo.cpp>

#	ifdef ALBA_PLATFORM_WINDOWS
#		include <examples/imgui_impl_win32.cpp>
#	endif

#	pragma warning( pop )   

#endif