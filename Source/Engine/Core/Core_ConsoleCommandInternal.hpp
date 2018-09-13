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

			//-------------------------------------------------------------------------------------
			// Name	:	theStorageSize
			// Desc	:	Max size to store directly inside command storage without allocating from
			//			the heap
			//-------------------------------------------------------------------------------------
			constexpr size_t theStorageSize = HardwareConstants::theL1CacheLineSize - sizeof(void*);

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			typedef uint32 CommandReturnCode;

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			struct CommandVTableBase
			{
				// Store the command in the vTable
				void (*Store)(CommandStorage& aCommandStorage, void* aValue);

				// Destroy the stored command
				void (*Destruct)(CommandStorage& aCommandStorage);

				// Invoke the command
				uint32 (*Invoke)(CommandStorage& aCommandStorage, void* anArgumentTuple);
			};

			//-------------------------------------------------------------------------------------
			// Name	:	CommandStorage
			// Desc	:	Stores a command, along with a vTable that will allow it to be executed
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

				static TCommandType& GetCommandInstance(CommandStorage& aCommandStorage)
				{
					return reinterpret_cast<TCommandType&>(aCommandStorage.myData);
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
					auto& command = GetCommandInstance(aCommandStorage);

					// We have arguments, pass the arguments tuple to the function
					// (std::apply will call the function with the correct args)
					if constexpr (sizeof...(TArgs) > 0)
					{
						typedef std::tuple<TArgs...> ArgumentsTuple;

						const auto& args = *reinterpret_cast<ArgumentsTuple*>(anArgumentTuple);
						return std::apply(command, args);
					}
					// Otherwise just call the command, no arguments to pass in
					else
					{
						(void*)anArgumentTuple;
						command();
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
				static const auto ConstructVTable(uint32(TCallable::*)(TArgs...))
				{
					return CommandVTableDerived<TClass, TArgs...>();
				}

				template <typename ...TArgs>
				static const auto ConstructVTable(uint32(TCallable::*)(TArgs...) const)
				{
					return CommandVTableDerived<const TCallable, TArgs...>();
				}

				// Functor version - use operator()
				// Assumes there's only one ::operator()
				template <typename ...TArgs>
				static const auto& GetVTable()
				{
					static auto ourVTable = ConstructVTable(&TCallable::operator());
					return ourVTable;
				}

				template <typename ...TArgs>
				static const auto& GetVTable(uint32(TCallable::*aMemberFunction)(TArgs...))
				{
					static auto ourVTable = ConstructVTable(aMemberFunction);
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
				static const auto ConstructVTable(uint32(*)(TArgs...))
				{
					return CommandVTableDerived<uint32(*)(TArgs...), TArgs...>();
				}

				template <typename ...TArgs>
				static const auto& GetVTable(uint32(*aFunction)(TArgs...))
				{
					static auto ourVTable = ConstructVTable(aFunction);
					return ourVTable;
				}
			};
		}
	}
}