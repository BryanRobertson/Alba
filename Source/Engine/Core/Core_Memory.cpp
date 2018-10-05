#include "Core_Precompile.hpp"
#include "Core_Memory.hpp"

#include <cstdlib>

namespace Alba
{
	namespace Core
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////
		#if defined(ALBA_RETAIL_BUILD)
			void* Malloc(size_t size, size_t alignment, size_t alignmentOffset, TAllocType allocType)
		#else
			void* Malloc(size_t size, size_t alignment, size_t alignmentOffset, TAllocType allocType, const char* description, const char* file, uint32 line)
		#endif
		{
			(void)alignment;
			(void)alignmentOffset;
			(void)allocType;

			#if !defined(ALBA_RETAIL_BUILD)
			(void)description;
			(void)file;
			(void)line;
			#endif

			return std::malloc(size);
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////
		#if defined(ALBA_RETAIL_BUILD)
			void* Realloc(void* pointer, size_t size)
		#else
			void* Realloc(void* pointer, size_t size, const char* file, uint32 line)
		#endif
		{
			#if !defined(ALBA_RETAIL_BUILD)
			(void)file;
			(void)line;
			#endif

			return std::realloc(pointer, size);
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////
		void Free(void* pointer)
		{
			std::free(pointer);
		}
	}
}
