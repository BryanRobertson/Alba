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
				using PrintCallback		= FixedFunction<void(ConsoleMessageType aMessageType, StringView aStr)>;
				using PrintCallbackId	= StronglyTypedId<uint32, PrintCallback> ;

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
				template <typename TCommand, typename ...TArgs, class=enable_if<is_invocable_v<int, TCommand, TArgs...> > >
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
				void RegisterCommand(StringView aCommandName, TClassType* anInstance, int (TClassType::*aCommand)(TArgs...) )
				{
					RegisterCommand(aCommandName, [=](TArgs&&... args) -> int
					{
						return std::invoke(aCommand, anInstance, std::forward<TArgs>(args)...);
					});
				}

				// Free function
				template <typename ...TArgs>
				void RegisterCommand(StringView aCommandName, int(*aCommand)(TArgs...))
				{
					using FunctionPointerType = int()(TArgs...);
					const auto& ourVTable = ConsoleInternal::FreeFunctionVTableLocator<FunctionPointerType>(aCommand);
						
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
				inline void		PrintWarning(StringView aFormat, TArgs&&... someArgs)
				{
					Print(ConsoleMessageType::Warning, aFormat, std::forward<TArgs>(someArgs)...);
				}

				template <typename... TArgs>
				inline void		PrintError(StringView aFormat, TArgs&&... someArgs)
				{
					Print(ConsoleMessageType::Error, aFormat, std::forward<TArgs>(someArgs)...);
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
				void ForEach_RegisteredCommandName(TIteratorFunc&& anItrFunc)
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
				using CommandStorage = ConsoleInternal::CommandStorage;

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