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
					ImGui::TextWrapped("Enter 'help' for help, press TAB to use text completion.");
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
					ImGui::PushFont(ImGuiModule::Get().GetConsoleFont());

					const bool commandLine = ImGui::InputText
					(
						"Input",
						&myInputBuffer[0],
						myInputBuffer.size(),
						ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory,
						(ImGuiTextEditCallback)&TextEditCallback, (void*)this
					);

					ImGui::PopFont();

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
		Core::Console& Console::GetBackEnd()
		{
			Core::ConsoleModule& consoleModule = Core::ConsoleModule::Get();
			ALBA_ASSERT(consoleModule.IsLoaded(), "Trying to get console backend, but console module isn't loaded!");

			return consoleModule.GetConsole();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Console::ExecCommand(Core::StringView aCommandLine)
		{
			Core::Console& consoleBackEnd = GetBackEnd();
			consoleBackEnd.Execute(aCommandLine);

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
		int Console::TextEditCallback(ImGuiTextEditCallbackData* data)
		{
			// Get console instance from user data
			Console* graphicsConsole = (Console*)data->UserData;
			Core::Console& consoleBackEnd = graphicsConsole->GetBackEnd();

			(void)consoleBackEnd;

#if 0
			// Handle ImGui events
			switch (data->EventFlag)
			{
				//----------------------------------------------------------------------------------
				// Callback completion
				//----------------------------------------------------------------------------------
				case ImGuiInputTextFlags_CallbackCompletion:
				{
					// Example of text completion

					// Locate beginning of current word
					const char* wordEnd = data->Buf + data->CursorPos;
					const char* wordStart = wordEnd;

					while (wordStart > data->Buf)
					{
						const char c = wordStart[-1];
						if (c == ' ' || c == '\t' || c == ',' || c == ';')
						{
							break;
						}

						wordStart--;
					}

					// Build a list of candidates
					ImVector<const char*> candidates;

					consoleBackEnd.ForEach_RegisteredCommandName([&](Core::StringView aCommandName)
					{
						//aCommandName.compare()
					});

					for (int i = 0; i < Commands.Size; i++)
						if (Strnicmp(Commands[i], word_start, (int)(word_end - word_start)) == 0)
							candidates.push_back(Commands[i]);

					if (candidates.Size == 0)
					{
						// No match
						AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
					}
					else if (candidates.Size == 1)
					{
						// Single match. Delete the beginning of the word and replace it entirely so we've got nice casing
						data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
						data->InsertChars(data->CursorPos, candidates[0]);
						data->InsertChars(data->CursorPos, " ");
					}
					else
					{
						// Multiple matches. Complete as much as we can, so inputing "C" will complete to "CL" and display "CLEAR" and "CLASSIFY"
						int match_len = (int)(word_end - word_start);
						for (;;)
						{
							int c = 0;
							bool all_candidates_matches = true;
							for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
								if (i == 0)
									c = toupper(candidates[i][match_len]);
								else if (c == 0 || c != toupper(candidates[i][match_len]))
									all_candidates_matches = false;
							if (!all_candidates_matches)
								break;
							match_len++;
						}

						if (match_len > 0)
						{
							data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
							data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
						}

						// List matches
						AddLog("Possible matches:\n");
						for (int i = 0; i < candidates.Size; i++)
							AddLog("- %s\n", candidates[i]);
					}
				}
				break;

			case ImGuiInputTextFlags_CallbackHistory:
			{
				// Example of HISTORY
				const int prev_history_pos = HistoryPos;
				if (data->EventKey == ImGuiKey_UpArrow)
				{
					if (HistoryPos == -1)
						HistoryPos = History.Size - 1;
					else if (HistoryPos > 0)
						HistoryPos--;
				}
				else if (data->EventKey == ImGuiKey_DownArrow)
				{
					if (HistoryPos != -1)
						if (++HistoryPos >= History.Size)
							HistoryPos = -1;
				}

				// A better implementation would preserve the data on the current input line along with cursor position.
				if (prev_history_pos != HistoryPos)
				{
					data->CursorPos = data->SelectionStart = data->SelectionEnd = data->BufTextLen = (int)snprintf(data->Buf, (size_t)data->BufSize, "%s", (HistoryPos >= 0) ? History[HistoryPos] : "");
					data->BufDirty = true;
				}
			}
			break;
			}
#endif
			return 0;

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