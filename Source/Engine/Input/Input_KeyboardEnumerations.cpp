#include "Input_Precompile.hpp"
#include "Input_KeyboardEnumerations.hpp"
#include "Core_Config.hpp"

namespace Alba
{
	//-----------------------------------------------------------------------------------------
	// Name	:	to_string
	// Desc	:	Convert an Input::Key to a string
	//-----------------------------------------------------------------------------------------
	Core::StringView to_string(Input::Key aKey)
	{
#if !defined(ALBA_RETAIL_BUILD)
		switch (aKey)
		{
			case Input::Key::LeftMouseButton:			return "LeftMouseButton";
			case Input::Key::RightMouseButton:			return "RightMouseButton";
			case Input::Key::Cancel:					return "Cancel";
			case Input::Key::MiddleMouseButton:			return "MiddleMouseButton";
			case Input::Key::XButton1:					return "XButton1";
			case Input::Key::XButton2:					return "XButton2";
			case Input::Key::Undefined_01:				return "Undefined_01";
			case Input::Key::Backspace:					return "Backspace";
			case Input::Key::Tab:						return "Tab";
			case Input::Key::Reserved_01:				return "Reserved_01";
			case Input::Key::Reserved_02:				return "Reserved_02";
			case Input::Key::Clear:						return "Clear";
			case Input::Key::Return:					return "Return";
			case Input::Key::Undefined_02:				return "Undefined_02";
			case Input::Key::Undefined_03:				return "Undefined_03";
			case Input::Key::Shift:						return "Shift";
			case Input::Key::Control:					return "Control";
			case Input::Key::Alt:						return "Alt";
			case Input::Key::Pause:						return "Pause";
			case Input::Key::CapsLock:					return "CapsLock";
			case Input::Key::Kana_Hanguel_Hangul:		return "Kana_Hanguel_Hangul";
			case Input::Key::Undefined_04:				return "Undefined_04";
			case Input::Key::Junja:						return "Junja";
			case Input::Key::Final:						return "Final";
			case Input::Key::Hanja_Kanji:				return "Hanja_Kanji";
			case Input::Key::Undefined_05:				return "Undefined_05";
			case Input::Key::Escape:					return "Escape";
			case Input::Key::Convert:					return "Convert";
			case Input::Key::NonConvert:				return "NonConvert";
			case Input::Key::Accept:					return "Accept";
			case Input::Key::ModeChange:				return "ModeChange";
			case Input::Key::SpaceBar:					return "SpaceBar";
			case Input::Key::PageUp:					return "PageUp";
			case Input::Key::PageDown:					return "PageDown";
			case Input::Key::End:						return "End";
			case Input::Key::Home:						return "Home";
			case Input::Key::LeftArrow:					return "LeftArrow";
			case Input::Key::UpArrow:					return "UpArrow";
			case Input::Key::RightArrow:				return "RightArrow";
			case Input::Key::DownArrow:					return "DownArrow";
			case Input::Key::Select:					return "Select";
			case Input::Key::Print:						return "Print";
			case Input::Key::Execute:					return "Execute";
			case Input::Key::PrintScreen:				return "PrintScreen";
			case Input::Key::Insert:					return "Insert";
			case Input::Key::Delete:					return "Delete";
			case Input::Key::Help:						return "Help";
			case Input::Key::Number0:					return "Number0";
			case Input::Key::Number1:					return "Number1";
			case Input::Key::Number2:					return "Number2";
			case Input::Key::Number3:					return "Number3";
			case Input::Key::Number4:					return "Number4";
			case Input::Key::Number5:					return "Number5";
			case Input::Key::Number6:					return "Number6";
			case Input::Key::Number7:					return "Number7";
			case Input::Key::Number8:					return "Number8";
			case Input::Key::Number9:					return "Number9";
			case Input::Key::Undefined_06:				return "Undefined_06";
			case Input::Key::Undefined_07:				return "Undefined_07";
			case Input::Key::Undefined_08:				return "Undefined_08";
			case Input::Key::Undefined_09:				return "Undefined_09";
			case Input::Key::Undefined_10:				return "Undefined_10";
			case Input::Key::Undefined_11:				return "Undefined_11";
			case Input::Key::Undefined_12:				return "Undefined_12";
			case Input::Key::A:							return "A";
			case Input::Key::B:							return "B";
			case Input::Key::C:							return "C";
			case Input::Key::D:							return "D";
			case Input::Key::E:							return "E";
			case Input::Key::F:							return "F";
			case Input::Key::G:							return "G";
			case Input::Key::H:							return "H";
			case Input::Key::I:							return "I";
			case Input::Key::J:							return "J";
			case Input::Key::K:							return "K";
			case Input::Key::L:							return "L";
			case Input::Key::M:							return "M";
			case Input::Key::N:							return "N";
			case Input::Key::O:							return "O";
			case Input::Key::P:							return "P";
			case Input::Key::Q:							return "Q";
			case Input::Key::R:							return "R";
			case Input::Key::S:							return "S";
			case Input::Key::T:							return "T";
			case Input::Key::U:							return "U";
			case Input::Key::V:							return "V";
			case Input::Key::W:							return "W";
			case Input::Key::X:							return "X";
			case Input::Key::Y:							return "Y";
			case Input::Key::Z:							return "Z";
			case Input::Key::LeftWindows:				return "LeftWindows";
			case Input::Key::RightWindows:				return "RightWindows";
			case Input::Key::Applications:				return "Applications";
			case Input::Key::Reserved_03:				return "Reserved_03";
			case Input::Key::Sleep:						return "Sleep";
			case Input::Key::Numpad0:					return "Numpad0";
			case Input::Key::Numpad1:					return "Numpad1";
			case Input::Key::Numpad2:					return "Numpad2";
			case Input::Key::Numpad3:					return "Numpad3";
			case Input::Key::Numpad4:					return "Numpad4";
			case Input::Key::Numpad5:					return "Numpad5";
			case Input::Key::Numpad6:					return "Numpad6";
			case Input::Key::Numpad7:					return "Numpad7";
			case Input::Key::Numpad8:					return "Numpad8";
			case Input::Key::Numpad9:					return "Numpad9";
			case Input::Key::Multiply:					return "Multiply";
			case Input::Key::Add:						return "Add";
			case Input::Key::Separator:					return "Separator";
			case Input::Key::Subtract:					return "Subtract";
			case Input::Key::Decimal:					return "Decimal";
			case Input::Key::Divide:					return "Divide";
			case Input::Key::F1:						return "F1";
			case Input::Key::VK_F2:						return "VK_F2";
			case Input::Key::VK_F3:						return "VK_F3";
			case Input::Key::VK_F4:						return "VK_F4";
			case Input::Key::VK_F5:						return "VK_F5";
			case Input::Key::VK_F6:						return "VK_F6";
			case Input::Key::VK_F7:						return "VK_F7";
			case Input::Key::VK_F8:						return "VK_F8";
			case Input::Key::VK_F9:						return "VK_F9";
			case Input::Key::VK_F10:					return "VK_F10";
			case Input::Key::VK_F11:					return "VK_F11";
			case Input::Key::VK_F12:					return "VK_F12";
			case Input::Key::VK_F13:					return "VK_F13";
			case Input::Key::VK_F14:					return "VK_F14";
			case Input::Key::VK_F15:					return "VK_F15";
			case Input::Key::VK_F16:					return "VK_F16";
			case Input::Key::VK_F17:					return "VK_F17";
			case Input::Key::VK_F18:					return "VK_F18";
			case Input::Key::VK_F19:					return "VK_F19";
			case Input::Key::VK_F20:					return "VK_F20";
			case Input::Key::VK_F21:					return "VK_F21";
			case Input::Key::VK_F22:					return "VK_F22";
			case Input::Key::VK_F23:					return "VK_F23";
			case Input::Key::VK_F24:					return "VK_F24";
			case Input::Key::Undefined_13:				return "Undefined_13";
			case Input::Key::Undefined_14:				return "Undefined_14";
			case Input::Key::Undefined_15:				return "Undefined_15";
			case Input::Key::Undefined_16:				return "Undefined_16";
			case Input::Key::Undefined_17:				return "Undefined_17";
			case Input::Key::Undefined_18:				return "Undefined_18";
			case Input::Key::Undefined_19:				return "Undefined_19";
			case Input::Key::Undefined_20:				return "Undefined_20";
			case Input::Key::NumLock:					return "NumLock";
			case Input::Key::ScrollLock:				return "ScrollLock";
			case Input::Key::OEM_Specific_01:			return "OEM_Specific_01";
			case Input::Key::OEM_Specific_02:			return "OEM_Specific_02";
			case Input::Key::OEM_Specific_03:			return "OEM_Specific_03";
			case Input::Key::OEM_Specific_04:			return "OEM_Specific_04";
			case Input::Key::OEM_Specific_05:			return "OEM_Specific_05";
			case Input::Key::Undefined_21:				return "Undefined_21";
			case Input::Key::Undefined_22:				return "Undefined_22";
			case Input::Key::Undefined_23:				return "Undefined_23";
			case Input::Key::Undefined_24:				return "Undefined_24";
			case Input::Key::Undefined_25:				return "Undefined_25";
			case Input::Key::Undefined_26:				return "Undefined_26";
			case Input::Key::Undefined_27:				return "Undefined_27";
			case Input::Key::Undefined_28:				return "Undefined_28";
			case Input::Key::LeftShift:					return "LeftShift";
			case Input::Key::RightShift:				return "RightShift";
			case Input::Key::LeftControl:				return "LeftControl";
			case Input::Key::RightControl:				return "RightControl";
			case Input::Key::LeftMenu:					return "LeftMenu";
			case Input::Key::RightMenu:					return "RightMenu";
			case Input::Key::BrowserBack:				return "BrowserBack";
			case Input::Key::BrowserForward:			return "BrowserForward";
			case Input::Key::BrowserRefresh:			return "BrowserRefresh";
			case Input::Key::BrowserStop:				return "BrowserStop";
			case Input::Key::BrowserSearch:				return "BrowserSearch";
			case Input::Key::BrowserFavorites:			return "BrowserFavorites";
			case Input::Key::BrowserHome:				return "BrowserHome";
			case Input::Key::VolumeMute:				return "VolumeMute";
			case Input::Key::VolumeDown:				return "VolumeDown";
			case Input::Key::VolumeUp:					return "VolumeUp";
			case Input::Key::MediaNextTrack:			return "MediaNextTrack";
			case Input::Key::MediaPrevTrack:			return "MediaPrevTrack";
			case Input::Key::MediaStop:					return "MediaStop";
			case Input::Key::MediaPlayPause:			return "MediaPlayPause";
			case Input::Key::LaunchMail:				return "LaunchMail";
			case Input::Key::LaunchMediaSelect:			return "LaunchMediaSelect";
			case Input::Key::LaunchApp1:				return "LaunchApp1";
			case Input::Key::LaunchApp2:				return "LaunchApp2";
			case Input::Key::Reserved_04:				return "Reserved_04";
			case Input::Key::Reserved_05:				return "Reserved_05";
			case Input::Key::OEM_01:					return "OEM_01";
			case Input::Key::OEM_PLUS:					return "OEM_PLUS";
			case Input::Key::OEM_COMMA:					return "OEM_COMMA";
			case Input::Key::OEM_MINUS:					return "OEM_MINUS";
			case Input::Key::OEM_PERIOD:				return "OEM_PERIOD";
			case Input::Key::OEM_02:					return "OEM_02";
			case Input::Key::OEM_03:					return "OEM_03";
			case Input::Key::Reserved_06:				return "Reserved_06";
			case Input::Key::Reserved_07:				return "Reserved_07";
			case Input::Key::Reserved_08:				return "Reserved_08";
			case Input::Key::Reserved_09:				return "Reserved_09";
			case Input::Key::Reserved_10:				return "Reserved_10";
			case Input::Key::Reserved_11:				return "Reserved_11";
			case Input::Key::Reserved_12:				return "Reserved_12";
			case Input::Key::Reserved_13:				return "Reserved_13";
			case Input::Key::Reserved_14:				return "Reserved_14";
			case Input::Key::Reserved_15:				return "Reserved_15";
			case Input::Key::Reserved_16:				return "Reserved_16";
			case Input::Key::Reserved_17:				return "Reserved_17";
			case Input::Key::Reserved_18:				return "Reserved_18";
			case Input::Key::Reserved_19:				return "Reserved_19";
			case Input::Key::Reserved_20:				return "Reserved_20";
			case Input::Key::Reserved_21:				return "Reserved_21";
			case Input::Key::Reserved_22:				return "Reserved_22";
			case Input::Key::Reserved_23:				return "Reserved_23";
			case Input::Key::Reserved_24:				return "Reserved_24";
			case Input::Key::Reserved_25:				return "Reserved_25";
			case Input::Key::Reserved_26:				return "Reserved_26";
			case Input::Key::Reserved_27:				return "Reserved_27";
			case Input::Key::Reserved_28:				return "Reserved_28";
			case Input::Key::Undefined_32:				return "Undefined_32";
			case Input::Key::Undefined_33:				return "Undefined_33";
			case Input::Key::Undefined_34:				return "Undefined_34";
			case Input::Key::OEM_04:					return "OEM_04";
			case Input::Key::OEM_05:					return "OEM_05";
			case Input::Key::OEM_06:					return "OEM_06";
			case Input::Key::OEM_07:					return "OEM_07";
			case Input::Key::OEM_08:					return "OEM_08";
			case Input::Key::Reserved_29:				return "Reserved_29";
			case Input::Key::Reserved_30:				return "Reserved_30";
			case Input::Key::OEM_102:					return "OEM_102";
			case Input::Key::OEM_Specific_06:			return "OEM_Specific_06";
			case Input::Key::OEM_Specific_07:			return "OEM_Specific_07";
			case Input::Key::ProcessKey:				return "ProcessKey";
			case Input::Key::OEM_Specific_08:			return "OEM_Specific_08";
			case Input::Key::Packet:					return "Packet";
			case Input::Key::Undefined_35:				return "Undefined_35";
			case Input::Key::OEM_Specific_09:			return "OEM_Specific_09";
			case Input::Key::OEM_Specific_10:			return "OEM_Specific_10";
			case Input::Key::OEM_Specific_11:			return "OEM_Specific_11";
			case Input::Key::OEM_Specific_12:			return "OEM_Specific_12";
			case Input::Key::OEM_Specific_13:			return "OEM_Specific_13";
			case Input::Key::OEM_Specific_14:			return "OEM_Specific_14";
			case Input::Key::OEM_Specific_15:			return "OEM_Specific_15";
			case Input::Key::OEM_Specific_16:			return "OEM_Specific_16";
			case Input::Key::OEM_Specific_17:			return "OEM_Specific_17";
			case Input::Key::OEM_Specific_18:			return "OEM_Specific_18";
			case Input::Key::OEM_Specific_19:			return "OEM_Specific_19";
			case Input::Key::OEM_Specific_20:			return "OEM_Specific_20";
			case Input::Key::OEM_Specific_21:			return "OEM_Specific_21";
			case Input::Key::Attn:						return "Attn";
			case Input::Key::Crsel:						return "Crsel";
			case Input::Key::Exsel:						return "Exsel";
			case Input::Key::EraseEOF:					return "EraseEOF";
			case Input::Key::Play:						return "Play";
			case Input::Key::Zoom:						return "Zoom";
			case Input::Key::NoName:					return "NoName";
			case Input::Key::PA1:						return "PA1";
			case Input::Key::OEM_Clear:					return "OEM_Clear";
		}
#endif

		return "";
	}
}