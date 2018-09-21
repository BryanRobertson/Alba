#pragma once

#include "Core_API.hpp"
#include "Core_StringView.hpp"
#include "Core_Any.hpp"
#include "Core_StringHash.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_Platform.hpp"
#include "Core_ConsoleCommandParser.hpp"

namespace Alba
{
	namespace Core
	{
		namespace ConsoleInternal
		{
			struct CommandStorage;

			//-------------------------------------------------------------------------------------
			// Name	:	theStorageSize
			// Desc	:	Max size to store directly inside command storage without allocating from
			//			the heap
			//-------------------------------------------------------------------------------------
			constexpr size_t theStorageSize = HardwareConstants::theL1CacheLineSize - sizeof(void*);

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			typedef int CommandReturnCode;

			namespace ErrorCodes
			{
				enum Code
				{
					ParseError = 1
				};
			}

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			struct CommandVTableBase
			{
				// Store the command in the vTable
				void (*Store)(CommandStorage& aCommandStorage, void* aValue);

				// Copy the command stored in the vTable
				void(*Copy)(const CommandStorage& aFrom, CommandStorage& aTo);

				// Store the command in the vTable
				void(*Move)(CommandStorage&& aFrom, CommandStorage& aTo);

				// Destroy the stored command
				void (*Destruct)(CommandStorage& aCommandStorage);

				// Invoke the command from a command string
				CommandReturnCode (*Invoke)(CommandStorage& aCommandStorage, StringView aCommandStr);
			};

			//-------------------------------------------------------------------------------------
			// Name	:	CommandStorage
			// Desc	:	Stores a command, along with a vTable that will allow it to be executed
			//-------------------------------------------------------------------------------------
			struct CommandStorage
			{
				typedef Core::AlignedStorage<theStorageSize> Storage;

				CommandStorage()
					: myVTable(nullptr)
				{

				}

				CommandStorage(const CommandStorage& aCopyFrom)
					: myVTable(aCopyFrom.myVTable)
				{
					if (myVTable)
					{
						myVTable->Copy(aCopyFrom, *this);
					}
				}

				CommandStorage(CommandStorage&& aMoveFrom)
					: myVTable(std::move(aMoveFrom.myVTable))
				{
					if (myVTable)
					{
						myVTable->Move(std::forward<CommandStorage>(aMoveFrom), *this);
					}
				}

				~CommandStorage()
				{
					if (myVTable)
					{
						myVTable->Destruct(*this);
					}					
				}

				CommandStorage& operator=(const CommandStorage& aCopyFrom)
				{
					if (myVTable)
					{
						myVTable->Copy(aCopyFrom, *this);
					}
					
					return *this;
				}

				CommandStorage& operator=(CommandStorage&& aMoveFrom)
				{
					if (myVTable)
					{
						myVTable->Move(std::forward<CommandStorage>(aMoveFrom), *this);
					}

					return *this;
				}

				const CommandVTableBase*	myVTable;
				Storage						myData;
			};

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			template <typename TCommandType, typename ...TArgs>
			struct CommandVTableDerived : public CommandVTableBase
			{
				typedef std::tuple<std::remove_const_t<std::remove_reference_t<TArgs>>...> ArgumentsTuple;

				CommandVTableDerived()
				{
					Store = &CommandVTableDerived<TCommandType, TArgs...>::StoreFunc;
					Destruct = &CommandVTableDerived<TCommandType, TArgs...>::DestructFunc;
					Invoke = &CommandVTableDerived<TCommandType, TArgs...>::InvokeFunc;
					Copy = &CommandVTableDerived<TCommandType, TArgs...>::CopyFunc;
					Move = &CommandVTableDerived<TCommandType, TArgs...>::MoveFunc;
				}

				static TCommandType& GetCommandInstance(CommandStorage& aCommandStorage)
				{
					return reinterpret_cast<TCommandType&>(aCommandStorage.myData);
				}

				static void StoreFunc(CommandStorage& aCommandStorage, void* aValue)
				{
					// TODO: Use constexpr if, and store larger objects on the heap
					static_assert
					(
						sizeof(TCommandType) < theStorageSize, 
						"Command object is too large to fit into storage!"
					);

					new (&aCommandStorage.myData) TCommandType(*reinterpret_cast<TCommandType*>(aValue));
				}

				static void CopyFunc(const CommandStorage& aFrom, CommandStorage& aTo)
				{
					void* target = (&aTo.myData);
					new (target) TCommandType(*reinterpret_cast<TCommandType*>(&aFrom.myData));
				}

				static void MoveFunc(CommandStorage&& aFrom, CommandStorage& aTo)
				{
					new (&aTo.myData) TCommandType(std::move(*reinterpret_cast<TCommandType*>(&aFrom.myData)));
					DestructFunc(aFrom);
				}

				static void DestructFunc(CommandStorage& aCommandStorage)
				{
					TCommandType* ptr = reinterpret_cast<TCommandType*>(&aCommandStorage.myData);
					ptr->~TCommandType();
				}

				static CommandReturnCode InvokeFunc(CommandStorage& aCommandStorage, StringView aCommandStr)
				{
					auto& command = GetCommandInstance(aCommandStorage);

					// We have arguments, pass the arguments tuple to the function
					// (std::apply will call the function with the correct args)
					if constexpr (sizeof...(TArgs) > 0)
					{
						ArgumentsTuple args;

						// Attempt to parse arguments, and if successful call the command
						const ConsoleCommandParser::ParseState parseState{ aCommandStr };
						if (ConsoleCommandParser::ParseArguments(parseState, args))
						{
							return std::apply(command, args);
						}
						else
						{
							return ErrorCodes::ParseError;
						}						
					}
					// Otherwise just call the command, no arguments to pass in
					else
					{
						(void)aCommandStr;

						return command();
					}
				}
			};

			//-------------------------------------------------------------------------------------
			// For any functor (object with one and exactly one operator() method)
			// Get a VTable for that functor type
			//-------------------------------------------------------------------------------------
			template <typename TCallable>
			struct MemberFunctionVTableLocator
			{
				template <typename ...TArgs>
				static const auto ConstructVTable(CommandReturnCode(TCallable::*)(TArgs...))
				{
					return CommandVTableDerived<TClass, TArgs...>();
				}

				template <typename ...TArgs>
				static const auto ConstructVTable(CommandReturnCode(TCallable::*)(TArgs...) const)
				{
					return CommandVTableDerived<const TCallable, TArgs...>();
				}

				template <typename ...TArgs>
				static const auto& GetVTable()
				{
					static auto ourVTable = ConstructVTable( &TCallable::operator() );
					return ourVTable;
				}
			};

			//-------------------------------------------------------------------------------------
			// For any Free function type
			// Get a VTable for that functor type
			//-------------------------------------------------------------------------------------
			struct FreeFunctionVTableLocator
			{
				// We pass operator() into this, so that we can find out what arguments it takes
				// Not sure if there's a better way to do this, but it seems to work
				template <typename ...TArgs>
				static const auto ConstructVTable(CommandReturnCode(*)(TArgs...))
				{
					return CommandVTableDerived<CommandReturnCode(*)(TArgs...), TArgs...>();
				}

				template <typename ...TArgs>
				static const auto& GetVTable(CommandReturnCode(*aFunction)(TArgs...))
				{
					static auto ourVTable = ConstructVTable(aFunction);
					return ourVTable;
				}
			};
		}
	}
}