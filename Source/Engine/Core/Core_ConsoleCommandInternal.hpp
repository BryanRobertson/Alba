#pragma once

#include "Core_API.hpp"
#include "Core_StringView.hpp"
#include "Core_Any.hpp"
#include "Core_StringHash.hpp"
#include "Core_TypeTraits.hpp"
#include "Core_Platform.hpp"

namespace Alba
{
	namespace Core
	{
		namespace ConsoleInternal
		{
			struct CommandStorage;

			constexpr size_t theStorageSize = HardwareConstants::theL1CacheLineSize - sizeof(void*);

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			struct CommandVTableBase
			{
				void (*Store)(CommandStorage& aCommandStorage, void* aValue);
				void (*Destruct)(CommandStorage& aCommandStorage);
				uint32 (*Invoke)(CommandStorage& aCommandStorage, void* anArgumentTuple);
			};

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			struct CommandStorage
			{
				typedef std::aligned_storage<theStorageSize>::type Storage;

				CommandStorage()
					: myVTable(nullptr)
				{

				}

				~CommandStorage()
				{
					if (myVTable)
					{
						myVTable->Destruct(*this);
					}					
				}

				const CommandVTableBase*	myVTable;
				Storage						myData;
			};

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			template <typename TCommandType, typename ...TArgs>
			struct CommandVTableDerived : public CommandVTableBase
			{
				CommandVTableDerived()
				{
					Store = &CommandVTableDerived<TCommandType, TArgs...>::StoreFunc;
					Destruct = &CommandVTableDerived<TCommandType, TArgs...>::DestructFunc;
					Invoke = &CommandVTableDerived<TCommandType, TArgs...>::InvokeFunc;
				}

				static void StoreFunc(CommandStorage& aCommandStorage, void* aValue)
				{
					new (&aCommandStorage.myData) TCommandType(*reinterpret_cast<TCommandType*>(aValue));
				}

				static void DestructFunc(CommandStorage& aCommandStorage)
				{
					reinterpret_cast<TCommandType*>(&aCommandStorage.myData);
				}

				static uint32 InvokeFunc(CommandStorage& aCommandStorage, void* anArgumentTuple)
				{
					const std::tuple<TArgs...>& args = *reinterpret_cast<std::tuple<TArgs...>*>(anArgumentTuple);
					auto& command = reinterpret_cast<TCommandType&>(aCommandStorage.myData);

					return std::apply(command, args);
				}
			};

			//-------------------------------------------------------------------------------------
			// For any functor (object with one and exactly one operator() method)
			// Get a VTable for that functor type
			//-------------------------------------------------------------------------------------
			template <typename TFunctor>
			struct FunctorVTableLocator
			{
				// We pass operator() into this, so that we can find out what arguments it takes
				// Not sure if there's a better way to do this, but it seems to work
				template <typename ...TArgs>
				static const auto ConstructVTable(uint32(TFunctor::*)(TArgs...))
				{
					return CommandVTableDerived<TFunctor, TArgs...>();
				}

				template <typename ...TArgs>
				static const auto ConstructVTable(uint32(TFunctor::*)(TArgs...) const)
				{
					return CommandVTableDerived<const TFunctor, TArgs...>();
				}

				template <typename ...TArgs>
				static const auto& GetVTable()
				{
					static auto ourVTable = ConstructVTable(&TFunctor::operator());
					return ourVTable;
				}
			};

#if 0
			template 
			<
				typename TCommand, 
				typename ...TArgs, 
				class = enable_if<is_invocable_v<CommandReturnCode, TCommand, TArgs...>> 
			>
			void RegisterCommand
			(
				NoCaseStringHash32 aCommandName, 
				const TCommand& aCommand
			)
			{
				(void)aCommandName;
				(void)aCommand;

				return;
			}

			template 
			<
				typename TClassType, 
				typename ...TArgs
			>
			void RegisterCommand
			(
				NoCaseStringHash32 aCommandName, 
				TClassType* anInstance, 
				CommandReturnCode(TClassType::*aCommand)(TArgs...)
			)
			{
				(void)aCommandName;
				(void)anInstance;
				(void)aCommand;

				return;
			}

			template <typename ...TArgs>
			void RegisterCommand(NoCaseStringHash32 aCommandName, CommandReturnCode(*aCommand)(TArgs...))
			{
				(void)aCommandName;
				(void)aCommand;

				return;
			}
#endif
		}
	}
}