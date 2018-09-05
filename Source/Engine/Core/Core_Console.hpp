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
				template <typename TCommand, typename ...TArgs, class=enable_if<is_invocable_v<CommandReturnCode, TCommand, TArgs...> > >
				void RegisterCommand(NoCaseStringHash32 aCommandName, TCommand&& aCommand)
				{
					const auto& vTable = ConsoleInternal::FunctorVTableLocator<TCommand>::GetVTable();

					auto itr = myCommands.emplace(aCommandName, CommandStorage());
					CommandStorage& storage = itr.first->second;

					storage.myVTable = &vTable;
					storage.myVTable->Store(storage, (void*)&aCommand);

					// TODO: Remove... this is just a test to make sure this works
					std::tuple<int, float> test(32, 3.14f);
					uint32 result=storage.myVTable->Invoke(storage, &test);
					++result;
					//
				}

				template <typename TClassType, typename ...TArgs>
				void RegisterCommand(NoCaseStringHash32 aCommandName, TClassType* anInstance, CommandReturnCode (TClassType::*aCommand)(TArgs...) )
				{
					(void)aCommandName;
					(void)anInstance;
					(void)aCommand;

					return;
				}

				template <typename ...TArgs>
				void RegisterCommand(NoCaseStringHash32 aCommandName, CommandReturnCode(*aCommand)(TArgs...))
				{
					typedef ConsoleInternal::CommandVTableDerived<decltype(aCommand)> VTable;
					static VTable ourVTable;
				
					CommandStorage& storage = myCommands.emplace(aCommandName, CommandStorage())->first.second;

					storage.myVTable = &ourVTable;
					storage.myVTable->Store(aCommand);
				}

				void UnregisterCommand(NoCaseStringHash32 aCommandName);

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
				// Private Types
				//=================================================================================
				typedef ConsoleInternal::CommandStorage CommandStorage;

				//=================================================================================
				// Private Methods
				//=================================================================================

				//=================================================================================
				// Private Data
				//=================================================================================
				VectorMap<PrintCallbackId, PrintCallback>		myPrintCallbacks;
				VectorMap<NoCaseStringHash32, CommandStorage>	myCommands;
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