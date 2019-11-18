#pragma once

#include "Core_API.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	StackAllocator
		// Desc	:	An allocator that pushes into a fixed block of memory
		//			The allocator can be reset by resetting the counter
		//-----------------------------------------------------------------------------------------
		class StackAllocator
		{
			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				explicit StackAllocator(const char* pName = "StackAllocator");
				StackAllocator(const StackAllocator& x);
				StackAllocator(const StackAllocator& x, const char* pName);

				//=================================================================================
				// Public Methods
				//=================================================================================
				void*		allocate(size_t n, int flags = 0);
				void*		allocate(size_t n, size_t alignment, size_t offset, int flags = 0);
				void		deallocate(void* p, size_t n);

				const char* get_name() const;
				void        set_name(const char* pName);

				StackAllocator& operator=(const StackAllocator& x);

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
		};		
	}
}