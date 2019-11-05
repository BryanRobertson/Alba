#pragma once

#include "Core.hpp"
#include "Core_AssertMutex.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	FreeList
		// Desc :	Partitions and manages a fixed-size chunk of memory
		//			Memory for free elements is used to maintain a linked-list of free elements
		//-----------------------------------------------------------------------------------------
		template <size_t TElementSize>
		class FreeList final
		{
			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				FreeList() = default;
				FreeList(const FreeList&) = delete;
				FreeList(FreeList&&) = default;

				//=================================================================================
				// Public Methods
				//=================================================================================
				void Init(byte* aStart, byte* anEnd)
				{
					ALBA_ASSERT(myNext == nullptr);
					ALBA_ASSERT(aStart < anEnd);

					const size_t count = (anEnd - aStart) / TElementSize;

					ALBA_ASSERT(count > 0);
					if (count == 0)
					{
						return;
					}

					std::memcpy(&myNext, &aStart, sizeof(myNext));
					FreeListNode* current = myNext;

					for (size_t i = 0; i < count - 1; ++i)
					{
						// Convert to byte so that we can advance the pointer
						// by the element size
						std::byte* bytePtr;
						std::memcpy(&bytePtr, &current, sizeof(bytePtr));

						bytePtr += TElementSize;

						// Copy back to the next pointer
						std::memcpy(&current->myNext, &bytePtr, sizeof(current->myNext));
						current = current->myNext;
					}

					current->myNext = nullptr;
				}


				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				ALBA_FORCEINLINE void* Allocate()
				{
					#if !defined(ALBA_RETAIL_BUILD)
						ScopedAssertMutexLock lock(myAssertMutex);
					#endif

					FreeListNode* next = myNext;
					myNext = next ? next->myNext : nullptr;

					return next;
				}

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				void Free(void* aPtr)
				{
					#if !defined(ALBA_RETAIL_BUILD)
						ALBA_ASSERT(aPtr >= myDebugData.myStart && aPtr < myDebugData.myEnd);
						ScopedAssertMutexLock lock(myAssertMutex);
					#endif

					FreeListNode* asFreeList;
					std::memcpy(&asFreeList, aPtr, sizeof(asFreeList));
					
					asFreeList->myNext = myNext;
					myNext = asFreeList;
				}

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				struct FreeListNode
				{
					FreeListNode* myNext = nullptr;
				};

				FreeListNode* myNext = nullptr;

				#if !defined(ALBA_RETAIL_BUILD)
					struct DebugData
					{
						void* myStart	= nullptr;
						void* myEnd		= nullptr;
					};

					DebugData myDebugData;
					AssertMutex myAssertMutex;
				#endif
		};
	}
}