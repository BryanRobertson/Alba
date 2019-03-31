#pragma once

#include "Core.hpp"
#include "Core_EnumerationTraits.hpp"
#include "Core_EnumerationSet.hpp"
#include "Core_Array.hpp"
#include "Core_Vector.hpp"

#include "Input_API.hpp"

namespace Alba
{
	namespace Input
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	Key
		// Desc	:	Enumeration representing keys on the keyboard 
		//			Note: Must be kept consistent with the enumeration traits below
		//				  or enumeration sets of keys will break
		//-----------------------------------------------------------------------------------------
		enum class Key : uint8
		{
			None					= 0x00,
			LeftMouseButton			= 0x01, // Left mouse button
			RightMouseButton		= 0x02, // Right mouse button
			Cancel					= 0x03, // Control - break processing
			MiddleMouseButton		= 0x04, // Middle mouse button(three - button mouse)
			XButton1				= 0x05, // X1 mouse button
			XButton2				= 0x06, // X2 mouse button
			Undefined_01			= 0x07, // Undefined
			Backspace				= 0x08, // BACKSPACE key
			Tab						= 0x09, // TAB key
			Reserved_01				= 0x0A, // Reserved
			Reserved_02				= 0x0B, // Reserved
			Clear					= 0x0C, // CLEAR key
			Return					= 0x0D, // ENTER key
			Undefined_02			= 0x0E,	// Undefined
			Undefined_03			= 0x0F,	// Undefined
			Shift					= 0x10, // SHIFT key
			Control					= 0x11, // CTRL key
			Alt						= 0x12, // ALT key (VK_MENU)
			Pause					= 0x13, // PAUSE key
			CapsLock				= 0x14,	// CAPS LOCK key
			Kana_Hanguel_Hangul		= 0x15, // IME Kana/Hanguel/Hangul mode
			Undefined_04			= 0x16, // Undefined
			Junja					= 0x17, // IME Junja mode
			Final					= 0x18, // IME final mode
			Hanja_Kanji				= 0x19, // IME Hanja/Kanji mode
			Undefined_05			= 0x1A, // Undefined
			Escape					= 0x1B, // ESC key
			Convert					= 0x1C, // IME Convert key
			NonConvert				= 0x1D, // IME NonConvert key
			Accept					= 0x1E, // IME Accept key
			ModeChange				= 0x1F, // IME mode change request
			SpaceBar				= 0x20, // SPACEBAR
			PageUp					= 0x21,	// PAGE UP key (VK_PRIOR)
			PageDown				= 0x22, // PAGE DOWN key
			End						= 0x23, // END key
			Home					= 0x24, // HOME key
			LeftArrow				= 0x25, // LEFT ARROW key
			UpArrow					= 0x26, // UP ARROW key
			RightArrow				= 0x27, // RIGHT ARROW key
			DownArrow				= 0x28, // DOWN ARROW key
			Select					= 0x29, // SELECT key
			Print					= 0x2A, // PRINT key
			Execute					= 0x2B, // EXECUTE key
			PrintScreen				= 0x2C, // PrintScreen (VK_SNAPSHOT)
			Insert					= 0x2D, // INS key
			Delete					= 0x2E, // DEL key
			Help					= 0x2F, // HELP key
			Number0					= 0x30, // 0 key
			Number1					= 0x31, // 1 key
			Number2					= 0x32, // 2 key
			Number3					= 0x33, // 3 key
			Number4					= 0x34, // 4 key
			Number5					= 0x35, // 5 key
			Number6					= 0x36, // 6 key
			Number7					= 0x37, // 7 key
			Number8					= 0x38, // 8 key
			Number9					= 0x39,	// 9 key
			Undefined_06			= 0x3A, // Undefined
			Undefined_07			= 0x3B, // Undefined
			Undefined_08			= 0x3C, // Undefined
			Undefined_09			= 0x3D, // Undefined
			Undefined_10			= 0x3E, // Undefined
			Undefined_11			= 0x3F, // Undefined
			Undefined_12			= 0x40, // Undefined
			A						= 0x41,
			B						= 0x42,
			C						= 0x43,
			D						= 0x44,
			E						= 0x45,
			F						= 0x46,
			G						= 0x47,
			H						= 0x48,
			I						= 0x49,
			J						= 0x4A,
			K						= 0x4B,
			L						= 0x4C,
			M						= 0x4D,
			N						= 0x4E,
			O						= 0x4F,
			P						= 0x50,
			Q						= 0x51,
			R						= 0x52,
			S						= 0x53,
			T						= 0x54,
			U						= 0x55,
			V						= 0x56,
			W						= 0x57,
			X						= 0x58,
			Y						= 0x59,
			Z						= 0x5A,
			LeftWindows				= 0x5B, // (VK_LWIN) Left Windows key(Natural keyboard)
			RightWindows			= 0x5C, // (VK_RWIN) Right Windows key(Natural keyboard)
			Applications			= 0x5D, // (VK_APPS) Applications key(Natural keyboard)
			Reserved_03				= 0x5E, // Reserved
			Sleep					= 0x5F, // Computer Sleep key
			Numpad0					= 0x60, // Numeric keypad 0 key
			Numpad1					= 0x61, // Numeric keypad 1 key
			Numpad2					= 0x62, // Numeric keypad 2 key
			Numpad3					= 0x63, // Numeric keypad 3 key
			Numpad4					= 0x64, // Numeric keypad 4 key
			Numpad5					= 0x65, // Numeric keypad 5 key
			Numpad6					= 0x66, // Numeric keypad 6 key
			Numpad7					= 0x67, // Numeric keypad 7 key
			Numpad8					= 0x68, // Numeric keypad 8 key
			Numpad9					= 0x69, // Numeric keypad 9 key
			Multiply				= 0x6A, // Multiply key
			Add						= 0x6B, // Add key
			Separator				= 0x6C, // Separator key
			Subtract				= 0x6D, // Subtract key
			Decimal					= 0x6E, // Decimal key
			Divide					= 0x6F, // Divide key
			F1						= 0x70, // F1 key
			VK_F2					= 0x71, // F2 key
			VK_F3					= 0x72, // F3 key
			VK_F4					= 0x73, // F4 key
			VK_F5					= 0x74, // F5 key
			VK_F6					= 0x75, // F6 key
			VK_F7					= 0x76, // F7 key
			VK_F8					= 0x77, // F8 key
			VK_F9					= 0x78, // F9 key
			VK_F10					= 0x79, // F10 key
			VK_F11					= 0x7A, // F11 key
			VK_F12					= 0x7B, // F12 key
			VK_F13					= 0x7C, // F13 key
			VK_F14					= 0x7D, // F14 key
			VK_F15					= 0x7E, // F15 key
			VK_F16					= 0x7F, // F16 key
			VK_F17					= 0x80, // F17 key
			VK_F18					= 0x81, // F18 key
			VK_F19					= 0x82, // F19 key
			VK_F20					= 0x83, // F20 key
			VK_F21					= 0x84, // F21 key
			VK_F22					= 0x85, // F22 key
			VK_F23					= 0x86, // F23 key
			VK_F24					= 0x87, // F24 key
			Undefined_13			= 0x88,	// Undefined
			Undefined_14			= 0x89,	// Undefined
			Undefined_15			= 0x8A, // Undefined
			Undefined_16			= 0x8B, // Undefined
			Undefined_17			= 0x8C, // Undefined
			Undefined_18			= 0x8D, // Undefined
			Undefined_19			= 0x8E, // Undefined
			Undefined_20			= 0x8F,	// Undefined
			NumLock					= 0x90, // NUM LOCK key
			ScrollLock				= 0x91, // SCROLL LOCK key	
			OEM_Specific_01			= 0x92,
			OEM_Specific_02			= 0x93,
			OEM_Specific_03			= 0x94,
			OEM_Specific_04			= 0x95,
			OEM_Specific_05			= 0x96,
			Undefined_21			= 0x97,
			Undefined_22			= 0x98,
			Undefined_23			= 0x99,
			Undefined_24			= 0x9A,
			Undefined_25			= 0x9B,
			Undefined_26			= 0x9C,
			Undefined_27			= 0x9D,
			Undefined_28			= 0x9E,
			Undefined_29			= 0x9F,
			LeftShift				= 0xA0, // Left SHIFT key
			RightShift				= 0xA1, // Right SHIFT key
			LeftControl				= 0xA2, // Left CONTROL key
			RightControl			= 0xA3, // Right CONTROL key
			LeftMenu				= 0xA4, // Left MENU key
			RightMenu				= 0xA5, // Right MENU key
			BrowserBack				= 0xA6, // Browser Back
			BrowserForward			= 0xA7, // Browser Forward
			BrowserRefresh			= 0xA8, // Browser Refresh
			BrowserStop				= 0xA9, // Browser Stop
			BrowserSearch			= 0xAA, // Browser Search key
			BrowserFavorites		= 0xAB, // Browser Favorites key
			BrowserHome				= 0xAC, // Browser Start and Home key
			VolumeMute				= 0xAD, // Volume Mute key
			VolumeDown				= 0xAE, // Volume Down key
			VolumeUp				= 0xAF, // Volume Up key
			MediaNextTrack			= 0xB0, // Next Track key
			MediaPrevTrack			= 0xB1, // Prev Track key
			MediaStop				= 0xB2, // Stop Media Key
			MediaPlayPause			= 0xB3, // Play / Pause Media key
			LaunchMail				= 0xB4, // Start Mail key
			LaunchMediaSelect		= 0xB5, // Select Media key
			LaunchApp1				= 0xB6, // Start Application 1 key
			LaunchApp2				= 0xB7, // Start Application 2 key
			Reserved_04				= 0xB8,
			Reserved_05				= 0xB9,
			OEM_01					= 0xBA, // Varies by keyboard For the US standard keyboard, the ';:' key
			OEM_PLUS				= 0xBB, // For any country / region, the '+' key
			OEM_COMMA				= 0xBC, // For any country / region, the ',' key
			OEM_MINUS				= 0xBD, // For any country / region, the '-' key
			OEM_PERIOD				= 0xBE, // For any country / region, the '.' key
			OEM_02					= 0xBF, // Varies by keyboard. For the US standard keyboard, the '/?' key
			OEM_03					= 0xC0, // Varies by keyboard. For the US standard keyboard, the '`~' key
			Reserved_06				= 0xC1,
			Reserved_07				= 0xC2,
			Reserved_08				= 0xC3,
			Reserved_09				= 0xC4,
			Reserved_10				= 0xC5,
			Reserved_11				= 0xC6,
			Reserved_12				= 0xC7,
			Reserved_13				= 0xC8,
			Reserved_14				= 0xC9,
			Reserved_15				= 0xCA,
			Reserved_16				= 0xCB,
			Reserved_17				= 0xCC,
			Reserved_18				= 0xCD, 
			Reserved_19				= 0xCE,
			Reserved_20				= 0xCF,
			Reserved_21				= 0xD0,
			Reserved_22				= 0xD1,
			Reserved_23				= 0xD2,
			Reserved_24				= 0xD3,
			Reserved_25				= 0xD4,
			Reserved_26				= 0xD5,
			Reserved_27				= 0xD6,
			Reserved_28				= 0xD7,
			Undefined_32			= 0xD8,
			Undefined_33			= 0xD9,
			Undefined_34			= 0xDA,
			OEM_04					= 0xDB, // Can vary by keyboard. For the US standard keyboard, the '[{' key
			OEM_05					= 0xDC, // Can vary by keyboard. For the US standard keyboard, the '\|' key
			OEM_06					= 0xDD, // Can vary by keyboard. For the US standard keyboard, the ']}' key
			OEM_07					= 0xDE, // Can vary by keyboard. For the US standard keyboard, the 'single-quote/double-quote' key
			OEM_08					= 0xDF, // Can vary by keyboard. 
			Reserved_29				= 0xE0,
			Reserved_30				= 0xE1,
			OEM_102					= 0xE2, // Either the angle bracket key or the backslash key on the RT 102 - key keyboard
			OEM_Specific_06			= 0xE3,
			OEM_Specific_07			= 0xE4,
			ProcessKey				= 0xE5, // IME PROCESS key
			OEM_Specific_08			= 0xE6, // OEM specific
			Packet					= 0xE7, // Used to pass Unicode characters as if they were keystrokes.The VK_PACKET key is the low word of a 32 - bit Virtual Key value used for non - keyboard input methods.For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP
			Undefined_35			= 0xE8, 
			OEM_Specific_09			= 0xE9,
			OEM_Specific_10			= 0xEA,
			OEM_Specific_11			= 0xEB,
			OEM_Specific_12			= 0xEC,
			OEM_Specific_13			= 0xED,
			OEM_Specific_14			= 0xEE,
			OEM_Specific_15			= 0xEF,
			OEM_Specific_16			= 0xF0,
			OEM_Specific_17			= 0xF1,
			OEM_Specific_18			= 0xF2,
			OEM_Specific_19			= 0xF3,
			OEM_Specific_20			= 0xF4,
			OEM_Specific_21			= 0xF5,
			Attn					= 0xF6, // Attn key
			Crsel					= 0xF7, // CrSel key
			Exsel					= 0xF8, // Exsel key
			EraseEOF				= 0xF9, // Erase EOF key (VK_EREOF)
			Play					= 0xFA, // Play key (VK_PLAY)
			Zoom					= 0xFB, // Zoom key
			NoName					= 0xFC, // Reserved
			PA1						= 0xFD, // PA1 key VK_PA1
			OEM_Clear				= 0xFE, // Clear key
		};

		//---------------------------------------------------------------------------------------------
		// Aliases
		//---------------------------------------------------------------------------------------------
		inline constexpr Key Key_Tilde = Key::OEM_03;
	}

	//---------------------------------------------------------------------------------------------
	// Name	:	get_all_enum_values<Input::Key>
	// Desc	:	Traits to get all valid entries in the Input::Key enumeration
	//			Used for KeySet (EnumerationSet<Key>)
	//---------------------------------------------------------------------------------------------
	template <>
	struct get_all_enum_values<Input::Key>
	{
		typedef Input::Key Key;

		static constexpr auto value = Core::Array<Key, 255>
		{
			Key::None,
			Key::LeftMouseButton,
			Key::RightMouseButton,
			Key::Cancel,
			Key::MiddleMouseButton,
			Key::XButton1,
			Key::XButton2,
			Key::Undefined_01,
			Key::Backspace,
			Key::Tab,
			Key::Reserved_01,
			Key::Reserved_02,
			Key::Clear,
			Key::Return,
			Key::Undefined_02,
			Key::Undefined_03,
			Key::Shift,
			Key::Control,
			Key::Alt,
			Key::Pause,
			Key::CapsLock,
			Key::Kana_Hanguel_Hangul,
			Key::Undefined_04,
			Key::Junja,
			Key::Final,
			Key::Hanja_Kanji,
			Key::Undefined_05,
			Key::Escape,
			Key::Convert,
			Key::NonConvert,
			Key::Accept,
			Key::ModeChange,
			Key::SpaceBar,
			Key::PageUp,
			Key::PageDown,
			Key::End,
			Key::Home,
			Key::LeftArrow,
			Key::UpArrow,
			Key::RightArrow,
			Key::DownArrow,
			Key::Select,
			Key::Print,
			Key::Execute,
			Key::PrintScreen,
			Key::Insert,
			Key::Delete,
			Key::Help,
			Key::Number0,
			Key::Number1,
			Key::Number2,
			Key::Number3,
			Key::Number4,
			Key::Number5,
			Key::Number6,
			Key::Number7,
			Key::Number8,
			Key::Number9,
			Key::Undefined_06,
			Key::Undefined_07,
			Key::Undefined_08,
			Key::Undefined_09,
			Key::Undefined_10,
			Key::Undefined_11,
			Key::Undefined_12,
			Key::A,
			Key::B,
			Key::C,
			Key::D,
			Key::E,
			Key::F,
			Key::G,
			Key::H,
			Key::I,
			Key::J,
			Key::K,
			Key::L,
			Key::M,
			Key::N,
			Key::O,
			Key::P,
			Key::Q,
			Key::R,
			Key::S,
			Key::T,
			Key::U,
			Key::V,
			Key::W,
			Key::X,
			Key::Y,
			Key::Z,
			Key::LeftWindows,
			Key::RightWindows,
			Key::Applications,
			Key::Reserved_03,
			Key::Sleep,
			Key::Numpad0,
			Key::Numpad1,
			Key::Numpad2,
			Key::Numpad3,
			Key::Numpad4,
			Key::Numpad5,
			Key::Numpad6,
			Key::Numpad7,
			Key::Numpad8,
			Key::Numpad9,
			Key::Multiply,
			Key::Add,
			Key::Separator,
			Key::Subtract,
			Key::Decimal,
			Key::Divide,
			Key::F1,
			Key::VK_F2,
			Key::VK_F3,
			Key::VK_F4,
			Key::VK_F5,
			Key::VK_F6,
			Key::VK_F7,
			Key::VK_F8,
			Key::VK_F9,
			Key::VK_F10,
			Key::VK_F11,
			Key::VK_F12,
			Key::VK_F13,
			Key::VK_F14,
			Key::VK_F15,
			Key::VK_F16,
			Key::VK_F17,
			Key::VK_F18,
			Key::VK_F19,
			Key::VK_F20,
			Key::VK_F21,
			Key::VK_F22,
			Key::VK_F23,
			Key::VK_F24,
			Key::Undefined_13,
			Key::Undefined_14,
			Key::Undefined_15,
			Key::Undefined_16,
			Key::Undefined_17,
			Key::Undefined_18,
			Key::Undefined_19,
			Key::Undefined_20,
			Key::NumLock,
			Key::ScrollLock,
			Key::OEM_Specific_01,
			Key::OEM_Specific_02,
			Key::OEM_Specific_03,
			Key::OEM_Specific_04,
			Key::OEM_Specific_05,
			Key::Undefined_21,
			Key::Undefined_22,
			Key::Undefined_23,
			Key::Undefined_24,
			Key::Undefined_25,
			Key::Undefined_26,
			Key::Undefined_27,
			Key::Undefined_28,
			Key::Undefined_29,
			Key::LeftShift,
			Key::RightShift,
			Key::LeftControl,
			Key::RightControl,
			Key::LeftMenu,
			Key::RightMenu,
			Key::BrowserBack,
			Key::BrowserForward,
			Key::BrowserRefresh,
			Key::BrowserStop,
			Key::BrowserSearch,
			Key::BrowserFavorites,
			Key::BrowserHome,
			Key::VolumeMute,
			Key::VolumeDown,
			Key::VolumeUp,
			Key::MediaNextTrack,
			Key::MediaPrevTrack,
			Key::MediaStop,
			Key::MediaPlayPause,
			Key::LaunchMail,
			Key::LaunchMediaSelect,
			Key::LaunchApp1,
			Key::LaunchApp2,
			Key::Reserved_04,
			Key::Reserved_05,
			Key::OEM_01,
			Key::OEM_PLUS,
			Key::OEM_COMMA,
			Key::OEM_MINUS,
			Key::OEM_PERIOD,
			Key::OEM_02,
			Key::OEM_03,
			Key::Reserved_06,
			Key::Reserved_07,
			Key::Reserved_08,
			Key::Reserved_09,
			Key::Reserved_10,
			Key::Reserved_11,
			Key::Reserved_12,
			Key::Reserved_13,
			Key::Reserved_14,
			Key::Reserved_15,
			Key::Reserved_16,
			Key::Reserved_17,
			Key::Reserved_18,
			Key::Reserved_19,
			Key::Reserved_20,
			Key::Reserved_21,
			Key::Reserved_22,
			Key::Reserved_23,
			Key::Reserved_24,
			Key::Reserved_25,
			Key::Reserved_26,
			Key::Reserved_27,
			Key::Reserved_28,
			Key::Undefined_32,
			Key::Undefined_33,
			Key::Undefined_34,
			Key::OEM_04,
			Key::OEM_05,
			Key::OEM_06,
			Key::OEM_07,
			Key::OEM_08,
			Key::Reserved_29,
			Key::Reserved_30,
			Key::OEM_102,
			Key::OEM_Specific_06,
			Key::OEM_Specific_07,
			Key::ProcessKey,
			Key::OEM_Specific_08,
			Key::Packet,
			Key::Undefined_35,
			Key::OEM_Specific_09,
			Key::OEM_Specific_10,
			Key::OEM_Specific_11,
			Key::OEM_Specific_12,
			Key::OEM_Specific_13,
			Key::OEM_Specific_14,
			Key::OEM_Specific_15,
			Key::OEM_Specific_16,
			Key::OEM_Specific_17,
			Key::OEM_Specific_18,
			Key::OEM_Specific_19,
			Key::OEM_Specific_20,
			Key::OEM_Specific_21,
			Key::Attn,
			Key::Crsel,
			Key::Exsel,
			Key::EraseEOF,
			Key::Play,
			Key::Zoom,
			Key::NoName,
			Key::PA1,
			Key::OEM_Clear
		};
	};

	//-----------------------------------------------------------------------------------------
	// Name	:	to_string
	// Desc	:	Convert an Input::Key to a string
	//-----------------------------------------------------------------------------------------
	extern Core::StringView to_string(Input::Key aKey);

	namespace Input
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		typedef Core::EnumerationSet<Key> KeySet;
	}
}