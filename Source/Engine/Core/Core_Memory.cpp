#include "Core_Precompile.hpp"
#include "Core_Memory.hpp"

#include <cstdlib>

namespace Core_Memory
{
	///////////////////////////////////////////////////////////////////////////////////////////////////
	void* Malloc(size_t size, size_t alignment, size_t alignmentOffset, TAllocType allocType, const char* description, const char* file, uint32 line)
	{
		(void)alignment;
		(void)alignmentOffset;
		(void)allocType;
		(void)description;
		(void)file;
		(void)line;

		return std::malloc(size);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////
	void* Realloc(void* pointer, size_t size, const char* file, uint32 line)
	{
		(void)file;
		(void)line;

		return std::realloc(pointer, size);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////
	void Free(void* pointer)
	{
		std::free(pointer);
	}
}
