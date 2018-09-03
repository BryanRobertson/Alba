#include "Graphics_Precompile.hpp"
#include "Graphics_Console.hpp"
#include "Graphics_ImGui.hpp"
#include "Graphics_ImGuiModule.hpp"

#include "Core_ConsoleModule.hpp"
#include "Core_Console.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Console::Console()
			: myLines(ourMaxConsoleItems)
			, myLineColours(ourMaxConsoleItems)
			, myHistory(ourConsoleHistorySize)
		{
			myInputBuffer.reserve(ourConsoleStringSize);
			myInputBuffer.assign(ourConsoleStringSize, '\0');
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Console::Render()
		{
			#if defined(ALBA_IMGUI_ENABLED)
			{
				//------------------------------------------------------------------------
				//------------------------------------------------------------------------
				if (!myIsConsoleVisible)
				{
					return;
				}

				static ImGuiTextFilter filter;

				bool reclaimFocus = false;
				bool copyToClipboard = false;
				bool scrollToBottom = false;

				//------------------------------------------------------------------------
				//------------------------------------------------------------------------
				ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
				if (!ImGui::Begin("Console", &myIsConsoleVisible))
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
						myIsConsoleVisible = false;
					}

					ImGui::EndPopup();
				}

				//------------------------------------------------------------------------
				// Help text
				//------------------------------------------------------------------------
				{
					ImGui::TextWrapped("Enter 'HELP' for help, press TAB to use text completion.");
					ImGui::Separator();
				}

				//------------------------------------------------------------------------
				// Buttons
				//------------------------------------------------------------------------
				{
					//------------------------------------------------------------------------
					// Clear
					//------------------------------------------------------------------------
					{
						if (ImGui::SmallButton("Clear"))
						{
							//ClearLog(); 
						}
						ImGui::SameLine();
					}

					//------------------------------------------------------------------------
					// Copy
					//------------------------------------------------------------------------
					{
						copyToClipboard = ImGui::SmallButton("Copy");
						ImGui::SameLine();
					}

					//------------------------------------------------------------------------
					// Scroll to bottom
					//------------------------------------------------------------------------
					{
						if (ImGui::SmallButton("Scroll to bottom"))
						{
							scrollToBottom = true;
						}
					}
					ImGui::Separator();
				}

				//------------------------------------------------------------------------
				// Filter
				//------------------------------------------------------------------------
				{
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
					{
						filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
					}					
					ImGui::PopStyleVar();

					ImGui::Separator();
				}

				//------------------------------------------------------------------------
				// Console lines
				//------------------------------------------------------------------------
				{
					ImGui::PushFont(ImGuiModule::Get().GetConsoleFont());

					const float ourFooterHeightToReserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
					ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ourFooterHeightToReserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText
					if (ImGui::BeginPopupContextWindow())
					{
						if (ImGui::Selectable("Clear"))
						{
							//ClearLog();
						}

						ImGui::EndPopup();
					}

					ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
					if (copyToClipboard)
					{
						ImGui::LogToClipboard();
					}
						
					ImVec4 col_default_text = ImGui::GetStyleColorVec4(ImGuiCol_Text);

					auto[line, lineColour] = std::make_tuple(myLines.begin(), myLineColours.begin());
					for (;line != myLines.end(); ++line,++lineColour)
					{
						if (!filter.PassFilter(line->c_str()))
						{ 
							continue;
						}

						const ImVec4 colour{ lineColour->x, lineColour->y, lineColour->z, lineColour->w };
						ImGui::PushStyleColor(ImGuiCol_Text, colour);
						ImGui::TextUnformatted(line->c_str());
						ImGui::PopStyleColor();
					}
					if (copyToClipboard)
					{
						ImGui::LogFinish();
					}

					if (scrollToBottom)
					{
						ImGui::SetScrollHere(1.0f);
					}

					scrollToBottom = false;
					ImGui::PopStyleVar();
					ImGui::EndChild();
					ImGui::Separator();

					ImGui::PopFont();
				}

				//------------------------------------------------------------------------
				// Command Line
				//------------------------------------------------------------------------
				{
					auto locTextEditCallback = [](ImGuiTextEditCallbackData* /*aData*/)
					{
						//Console* graphicsConsole = (Console*)aData->UserData;
						return 0;
					};

					const bool commandLine = ImGui::InputText
					(
						"Input",
						&myInputBuffer[0],
						myInputBuffer.size(),
						ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory,
						(ImGuiTextEditCallback)&locTextEditCallback, (void*)this
					);

					if (commandLine)
					{
						Core::StringView command(&myInputBuffer[0], myInputBuffer.size());
						while ( !command.empty() && (std::isblank(command.back()) || std::iscntrl(command.back())) )
						{
							command.remove_suffix(1);
						}

						if (!command.empty())
						{
							ExecCommand(command);
						}

						myInputBuffer.assign(ourConsoleStringSize, '\0');
						
						reclaimFocus = true;
					}
				}

				// Demonstrate keeping focus on the input box
				ImGui::SetItemDefaultFocus();
				if (reclaimFocus)
				{
					ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
				}

				ImGui::End();
			}
			#endif
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Console::ExecCommand(Core::StringView aCommandLine)
		{
			Core::ConsoleModule& consoleModule = Core::ConsoleModule::Get();
			if (consoleModule.IsLoaded())
			{
				Core::Console& consoleBackend = consoleModule.GetConsole();
				consoleBackend.Print(Alba::Core::ConsoleMessageType::Info, aCommandLine);
			}

			myHistory.push_back(ConsoleString(aCommandLine.begin(), aCommandLine.end()));
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Console::Print(Alba::Core::ConsoleMessageType aMessageType, Alba::Core::StringView aMessage)
		{
			#if defined(ALBA_IMGUI_ENABLED)
			{
				Math::Vector4f colour;
				switch (aMessageType)
				{
					case Alba::Core::ConsoleMessageType::Error:
					{
						colour = Math::Vector4f(1.0f, 0.4f, 0.4f, 1.0f);
					}
					break;

					case Alba::Core::ConsoleMessageType::Warning:
					{
						colour = Math::Vector4f(1.0f, 1.0f, 0.4f, 1.0f);
					}
					break;

					default:
					{
						const auto defaultColour = ImGui::GetStyleColorVec4(ImGuiCol_Text);
						colour[0] = defaultColour.x;
						colour[1] = defaultColour.y;
						colour[2] = defaultColour.z;
						colour[3] = defaultColour.w;
					}
					break;	
				}

				myLineColours.push_back(colour);
				myLines.push_back(ConsoleString(aMessage.begin(), aMessage.end()));
			}
			#else
			{
				(void)aMessageType;
				(void)aMessage;
			}
			#endif
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Console::Show()
		{
			myIsConsoleVisible = true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Console::Hide()
		{
			myIsConsoleVisible = false;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Console::ToggleVisibility()
		{
			myIsConsoleVisible = !myIsConsoleVisible;
		}
	}
}