#include "Graphics_Precompile.hpp"
#include "Graphics_ConsoleModule.hpp"
#include "Graphics_ImGui.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool ConsoleModule::OnLoad(Core::AnyDictionary /*someParameters*/)
		{
			myShowConsole = true;

			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ConsoleModule::OnUnload()
		{
			myShowConsole = false;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ConsoleModule::Render()
		{
			#if defined(ALBA_IMGUI_ENABLED)
			{
				if (!myShowConsole)
				{
					return;
				}

				//if ( ImGui::IsKeyPressed(ImGui::Key))
				{

				}

				//------------------------------------------------------------------------
				//------------------------------------------------------------------------
				ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
				if (!ImGui::Begin("Console", &myShowConsole))
				{
					ImGui::End();
					return;
				}

				//------------------------------------------------------------------------
				//------------------------------------------------------------------------
				if (ImGui::BeginPopupContextItem())
				{
					if (ImGui::MenuItem("Close Console"))
					{
						myShowConsole = false;
					}

					ImGui::EndPopup();
				}

				//------------------------------------------------------------------------
				// Help text
				//------------------------------------------------------------------------
				{
					ImGui::TextWrapped("Enter 'HELP' for help, press TAB to use text completion.");
				}

				//------------------------------------------------------------------------
				// Filter
				//------------------------------------------------------------------------
				{
					ImGui::Separator();

					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

					static ImGuiTextFilter filter;
					filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
					ImGui::PopStyleVar();
					ImGui::Separator();
				}

				ImGui::End();
			}
			#endif
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ConsoleModule::Show()
		{
			myShowConsole = true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ConsoleModule::Hide()
		{
			myShowConsole = false;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void ConsoleModule::ToggleVisibility()
		{
			myShowConsole = !myShowConsole;
		}
	}
}