#include "Graphics_Precompile.hpp"
#include "Graphics_Console.hpp"
#include "Graphics_ImGui.hpp"
#include "Graphics_ImGuiModule.hpp"

#include "Core_ConsoleModule.hpp"
#include "Core_Console.hpp"
#include "Core_Vector.hpp"
#include "Core_Profile.hpp"

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
				ALBA_PROFILE_SCOPED(GraphicsConsole_Render);

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
							Clear(); 
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
							Clear();
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
						ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory | ImGuiInputTextFlags_CallbackCharFilter,
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
		void Console::Clear()
		{
			myLines.clear();
			myLineColours.clear();
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

			using Core::ConsoleMessageType;

			// Handle ImGui events
			switch (data->EventFlag)
			{
				//----------------------------------------------------------------------------------
				// Filter
				//----------------------------------------------------------------------------------
				case ImGuiInputTextFlags_CallbackCharFilter:
				{
					// Filter out the ~ key since it's used to toggle the console
					if (data->EventChar == '~')
					{
						return 1;
					}
				}
				break;

				//----------------------------------------------------------------------------------
				// Completion
				//----------------------------------------------------------------------------------
				case ImGuiInputTextFlags_CallbackCompletion:
				{
					// Scan backwards to locate beginning of current word
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

					const Core::StringView word(wordStart, std::distance(wordStart, wordEnd));

					// Build a list of candidates
					Core::FixedVector<Core::StringView, 64> candidates;

					consoleBackEnd.ForEach_RegisteredCommandName([&](Core::StringView aCommandName)
					{
						if (aCommandName.starts_with(word))
						{
							candidates.push_back(aCommandName);
						}
					});

					if (candidates.size() == 0)
					{
						// No match
					}
					else if (candidates.size() == 1)
					{
						// Single match. Delete the beginning of the word and replace it entirely so we've got nice casing
						data->DeleteChars((int)(wordStart - data->Buf), (int)(wordEnd - wordStart));
						data->InsertChars(data->CursorPos, candidates[0].data());
					}
					else
					{
						// Multiple matches. Complete as much as we can, so inputing "C" will complete to "CL" and display "CLEAR" and "CLASSIFY"
						size_t matchLength = word.length();
						for (;;)
						{
							int c = 0;
							bool allCandidatesMatches = true;

							for (size_t index = 0; index < candidates.size() && allCandidatesMatches; ++index)
							{
								if (index == 0)
								{
									c = std::tolower(candidates[index][matchLength]);
								}
								else if (c == 0 || c != std::tolower(candidates[index][matchLength]))
								{
									allCandidatesMatches = false;
								}									
							}

							if (!allCandidatesMatches)
							{
								break;
							}

							++matchLength;
						}

						if (matchLength > 0)
						{
							data->DeleteChars((int)(wordStart - data->Buf), (int)(wordEnd - wordStart));
							data->InsertChars(data->CursorPos, candidates[0].data(), candidates[0].data() + matchLength);
						}				
					}
				}
				break;

				//----------------------------------------------------------------------------------
				// History
				//----------------------------------------------------------------------------------
				case ImGuiInputTextFlags_CallbackHistory:
				{
					//History
					const int prevHistoryPos = graphicsConsole->myHistoryIndex;
					if (data->EventKey == ImGuiKey_UpArrow)
					{
						if (graphicsConsole->myHistoryIndex == -1)
						{
							graphicsConsole->myHistoryIndex = static_cast<int>(graphicsConsole->myHistory.size()) - 1;
						}
						else if (graphicsConsole->myHistoryIndex > 0)
						{
							--graphicsConsole->myHistoryIndex;
						}
					}
					else if (data->EventKey == ImGuiKey_DownArrow)
					{
						if (graphicsConsole->myHistoryIndex != -1)
						{
							if (++graphicsConsole->myHistoryIndex >= graphicsConsole->myHistory.size())
							{
								graphicsConsole->myHistoryIndex = -1;
							}
						}
					}

					// A better implementation would preserve the data on the current input line along with cursor position.
					if (prevHistoryPos != graphicsConsole->myHistoryIndex)
					{
						data->CursorPos = data->SelectionStart = data->SelectionEnd = data->BufTextLen = (int)snprintf(data->Buf, (size_t)data->BufSize, "%s", (graphicsConsole->myHistoryIndex >= 0) ? graphicsConsole->myHistory[graphicsConsole->myHistoryIndex].c_str() : "");
						data->BufDirty = true;
					}
				}
				break;
			}

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void Console::Show()
		{
			myIsConsoleVisible = true;
			myWasConsoleShownThisFrame = true;
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
			myWasConsoleShownThisFrame = myIsConsoleVisible;
		}
	}
}