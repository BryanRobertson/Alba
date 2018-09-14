#pragma once

#include "Core.hpp"
#include "Core_RingBuffer.hpp"
#include "Core_Console.hpp"
#include "Math_Vector.hpp"

#include "Graphics_API.hpp"

struct ImGuiTextEditCallbackData;

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	Console
		// Desc	:	Used exclusively by the graphical console module to store console state
		//			and render the console using ImGui
		//-----------------------------------------------------------------------------------------
		class Console
		{
			public:

				friend class ConsoleModule;

				//=================================================================================
				// Public Constructors
				//=================================================================================
				Console();

				//=================================================================================
				// Public Methods
				//=================================================================================
				void			Render();
				
				void			Show();
				void			Hide();
				void			ToggleVisibility();

				Core::Console&	GetBackEnd();

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				void		ExecCommand(Core::StringView aCommandLine);
				void		Print(Alba::Core::ConsoleMessageType aMessageType, Alba::Core::StringView aMessage);

				static int	TextEditCallback(ImGuiTextEditCallbackData* aCallbackData);

				//=================================================================================
				// Private Types
				//=================================================================================
				static constexpr size_t ourConsoleStringSize = 256;
				static constexpr size_t ourMaxConsoleItems = 256;
				static constexpr size_t ourConsoleHistorySize = 64;

				typedef Core::FixedString<ourConsoleStringSize>						ConsoleString;
				typedef Core::FixedVector<char, ourConsoleStringSize>				ConsoleInputBuffer;

				typedef Core::FixedRingBuffer<ConsoleString, ourMaxConsoleItems>	ConsoleItems;
				typedef Core::FixedRingBuffer<Math::Vector4f, ourMaxConsoleItems>	ConsoleItemColours;
				typedef Core::FixedRingBuffer<ConsoleString, ourConsoleHistorySize>	ConsoleHistory;

				//=================================================================================
				// Private Data
				//=================================================================================
				ConsoleInputBuffer		myInputBuffer;
				ConsoleItems			myLines;
				ConsoleItemColours		myLineColours;
				ConsoleHistory			myHistory;

				bool					myIsConsoleVisible = true;
		};
	}
}