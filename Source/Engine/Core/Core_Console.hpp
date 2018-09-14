#pragma once

#include "Core.hpp"
#include "Core_StringView.hpp"
#include "Core_Function.hpp"
#include "Core_VectorMap.hpp"
#include "Core_StronglyTypedId.hpp"
#include "Core_ConsoleCommandInternal.hpp"

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

				typedef uint32 CommandReturnCode;

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

				// Functor/Lambda
				template <typename TCommand, typename ...TArgs, class=enable_if<is_invocable_v<CommandReturnCode, TCommand, TArgs...> > >
				void RegisterCommand(StringView aCommandName, TCommand&& aCommand)
				{
					const auto& ourVTable = ConsoleInternal::MemberFunctionVTableLocator<TCommand>::GetVTable();
					
					if (CommandStorage* storage = InsertCommand(aCommandName))
					{
						storage->myVTable = &ourVTable;
						storage->myVTable->Store(*storage, (void*)&aCommand);
					}
				}

				// Member function pointer
				template <typename TClassType, typename ...TArgs>
				void RegisterCommand(StringView aCommandName, TClassType* anInstance, CommandReturnCode (TClassType::*aCommand)(TArgs...) )
				{
					// Just use std::bind and call the 
					RegisterCommand(std::bind(anInstance, aCommand));
				}

				// Free function
				template <typename ...TArgs>
				void RegisterCommand(StringView aCommandName, CommandReturnCode(*aCommand)(TArgs...))
				{
					typedef CommandReturnCode(*FunctionType)(TArgs...);
					const auto& ourVTable = ConsoleInternal::FreeFunctionVTableLocator<FunctionType>(aCommand);
						
					if (CommandStorage* storage = InsertCommand(aCommandName))
					{
						storage->myVTable = &ourVTable;
						storage->myVTable->Store(*storage, (void*)aCommand);
					}
				}

				inline void		UnregisterCommand(StringView aCommandName);
				inline void		UnregisterCommand(NoCaseStringHash32 aCommandNameId);

				//---------------------------------------------------------------------------------
				// Execute command
				//---------------------------------------------------------------------------------
				void			Execute(StringView aCommand);

				//---------------------------------------------------------------------------------
				// Print
				//---------------------------------------------------------------------------------
				template <typename... TArgs>
				inline void		PrintInfo(StringView aFormat, TArgs&&... someArgs)
				{
					Print(ConsoleMessageType::Info, aFormat, std::forward<TArgs>(someArgs)...);
				}

				template <typename... TArgs>
				inline void		Print(ConsoleMessageType aMessageType, StringView aFormat, TArgs&&... someArgs);
				void			Print(ConsoleMessageType aMessageType, StringView aStr);

				PrintCallbackId RegisterPrintCallback(const PrintCallback& aCallback);
				void		    UnregisterPrintCallback(PrintCallbackId anId);

				//---------------------------------------------------------------------------------
				// Registered command iterator
				//---------------------------------------------------------------------------------
				template <typename TIteratorFunc>
				void ForEach_RegisteredCommandName(TIteratorFunc& anItrFunc)
				{
					for (const auto& itr : myCommandNames)
					{
						anItrFunc(StringView(itr.second));
					}
				}

			private:

				//=================================================================================
				// Private Types
				//=================================================================================
				typedef ConsoleInternal::CommandStorage CommandStorage;

				//=================================================================================
				// Private Methods
				//=================================================================================
				CommandStorage*	InsertCommand(StringView aCommandName);

				void			RegisterInternalCommands();

				//=================================================================================
				// Private Data
				//=================================================================================
				VectorMap<PrintCallbackId, PrintCallback>		myPrintCallbacks;

				VectorMap<NoCaseStringHash32, CommandStorage>	myCommands;
				VectorMap<NoCaseStringHash32, String>			myCommandNames;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		template <typename... TArgs>
		void Console::Print(ConsoleMessageType aMessageType, StringView aFormat, TArgs&&... someArgs)
		{
			const auto outputStr = Core::FormatString<256>(aFormat.data(), std::forward<TArgs>(someArgs)...);
			Print(aMessageType, StringView(outputStr.c_str()));
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void Console::UnregisterCommand(StringView aCommandName)
		{
			const Core::NoCaseStringHash32 commandNameId{ aCommandName };
			UnregisterCommand(commandNameId);
		}

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		void Console::UnregisterCommand(NoCaseStringHash32 aCommandNameId)
		{
			myCommands.erase(aCommandNameId);
			myCommandNames.erase(aCommandNameId);
		}
	}
}