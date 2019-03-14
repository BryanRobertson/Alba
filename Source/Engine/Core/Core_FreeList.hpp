#pragma once

#include "Core.hpp"

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
				FreeList(void* aStart, void* anEnd)
				{
					ALBA_ASSERT(aStart < anEnd);
					const size_t count = (anEnd - aStart) / TElementSize;

					ALBA_ASSERT(count > 0);
					if (count == 0)
					{
						return;
					}

					myNext = static_cast<FreeList*>(aStart);
					FreeList* current = myNext;

					for (size_t i = 0; i < count-1; ++i)
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

				//=================================================================================
				// Public Methods
				//=================================================================================
				void* Allocate()
				{
					void* entry = myNext;

					myNext = myNext ? myNext->myNext : nullptr;
					return entry;
				}

				void Free(void* aPtr)
				{
					#if !defined(ALBA_RETAIL_BUILD)
						ALBA_ASSERT(aPtr >= myStart && aPtr < myEnd);
					#endif

					FreeList* asFreeList;
					std::memcpy(&asFreeList, aPtr, sizeof(asFreeList));
					
					asFreeList->myNext = myNext;
					myNext = asFreeList;
				}

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				FreeList* myNext = nullptr;

				#if !defined(ALBA_RETAIL_BUILD)
					struct DebugData
					{
						void*	myStart = nullptr;
						void*	myEnd = nullptr;
					};

					DebugData myDebugData;
				#endif
		};
	}
}