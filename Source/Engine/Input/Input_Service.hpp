#pragma once

#include "Core.hpp"
#include "Input_API.hpp"
#include "Input_Keyboard.hpp"
#include "Core_EnumerationSet.hpp"

#include "Core_AnyDictionary.hpp"

namespace Alba
{
	namespace Core
	{
		class Time;
	}

	namespace Input
	{
		//------------------------------------------------------------------------------------------
		// Name	:	InputServiceStateFlag
		// Desc	:	State flags for the input service that affect behavior
		//------------------------------------------------------------------------------------------
		enum InputServiceStateFlag
		{
			UIHasExclusiveKeyboardFocus,
			UIHasExclusiveMouseFocus,
			UIHasExclusiveGamepadFocus,

			enum_traits_end_value,
			enum_traits_start_value = UIHasExclusiveKeyboardFocus,
			enum_traits_is_contiguous = 1,
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		typedef Core::EnumerationSet<InputServiceStateFlag> InputServiceStateFlags;

		//-----------------------------------------------------------------------------------------
		// Name	:	InputService
		// Desc	:	Provides access to input devices, and updates their state every frame
		//-----------------------------------------------------------------------------------------
		class ALBA_INPUT_API InputService final
		{
			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				InputService();
				InputService(const InputService&) = delete;
				InputService(InputService&&) = delete;

				~InputService();

				//=================================================================================
				// Public Methods
				//=================================================================================
				uint32	Init(const Core::AnyDictionary& someParams);
				void	ShutDown();

				void	BeginFrame();
				void	Update(const Core::Time& aTime);

				//---------------------------------------------------------------------------------
				// Input Devices
				//---------------------------------------------------------------------------------
				inline const Keyboard& GetKeyboard() const;

				//---------------------------------------------------------------------------------
				// Accessors
				//---------------------------------------------------------------------------------
				inline InputServiceStateFlags	GetStateFlags() const;
				inline InputServiceStateFlags&	GetStateFlagsMutable();

				//---------------------------------------------------------------------------------
				// Operator overloads
				//---------------------------------------------------------------------------------
				InputService& operator=(const InputService&) = delete;
				InputService& operator=(InputService&&) = delete;

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				void*						myWindowHandle	= nullptr;
				Keyboard					myKeyboard;
				InputServiceStateFlags		myStateFlags;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		inline const Keyboard& InputService::GetKeyboard() const
		{
			return myKeyboard;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		inline InputServiceStateFlags InputService::GetStateFlags() const
		{
			return myStateFlags;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		inline InputServiceStateFlags& InputService::GetStateFlagsMutable()
		{
			return myStateFlags;
		}
	}
}