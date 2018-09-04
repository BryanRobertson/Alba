#pragma once

#include "Core.hpp"
#include "Core_StringView.hpp"
#include "Core_Function.hpp"
#include "Core_VectorMap.hpp"
#include "Core_StronglyTypedId.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	ConsoleMessageType
		// Desc	:	Type of message printed to the console (can be used for output colouring, etc)
		//-----------------------------------------------------------------------------------------
		enum class ConsoleMessageType
		{
			Info,
			Warning,
			Error
		};

		class ConsoleCommand;

		//-----------------------------------------------------------------------------------------
		// Name	:	Console
		// Desc :	Standard Quake/style command console
		//			Executes commands and registers config variables that can be modified at runtime
		//-----------------------------------------------------------------------------------------
		class ALBA_CORE_API Console final
		{
			public:

				//=================================================================================
				// Public Types
				//=================================================================================
				typedef FixedFunction<void(ConsoleMessageType aMessageType, StringView aStr)> PrintCallback;
				typedef StronglyTypedId<uint32, PrintCallback> PrintCallbackId;

				//=================================================================================
				// Public Constructors
				//=================================================================================
				Console();
				~Console();

				//=================================================================================
				// Public Methods
				//=================================================================================

				//---------------------------------------------------------------------------------
				// Register/Unregister commands
				//---------------------------------------------------------------------------------
				template <typename TCommandType>
				inline void		RegisterCommand();

				void			UnregisterCommand(NoCaseStringHash32 aCommandName);

				//---------------------------------------------------------------------------------
				// Execute command
				//---------------------------------------------------------------------------------
				void			Execute(StringView aCommand);

				//---------------------------------------------------------------------------------
				// Print
				//---------------------------------------------------------------------------------
				template <typename... TArgs>
				inline void		Print(ConsoleMessageType aMessageType, StringView aFormat, TArgs&&... someArgs);
				void			Print(ConsoleMessageType aMessageType, StringView aStr);

				PrintCallbackId RegisterPrintCallback(const PrintCallback& aCallback);
				void		    UnregisterPrintCallback(PrintCallbackId anId);

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				void			RegisterCommand(ConsoleCommand& aCommand);

				//=================================================================================
				// Private Data
				//=================================================================================
				VectorMap<PrintCallbackId, PrintCallback>		myPrintCallbacks;
				VectorMap<NoCaseStringHash32, ConsoleCommand*>	myConsoleCommands;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename... TArgs>
		void Console::Print(ConsoleMessageType aMessageType, StringView aFormat, TArgs&&... someArgs)
		{
			const auto outputStr = Core::FormatString<256>(aFormat.data(), std::forward<TArgs>(someArgs)...);
			Print(aMessageType, StringView(outputStr.c_str()));
		}
	}
}