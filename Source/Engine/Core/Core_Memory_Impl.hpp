//-------------------------------------------------------------------------------------------------
// Name      : Core_Memory_Impl.hpp
// Desc      : Implementation of new/delete overloads. Include this in a single .cpp file of your 
//			   project
//
// Author    : Bryan Robertson
// Date      : 2016/11/20
//-------------------------------------------------------------------------------------------------
#pragma once

#include "Core_Memory.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////
void* ALBA_CDECL operator new(size_t size, size_t alignment, size_t alignmentOffset, Core_Memory::TAllocType allocType, const char* description, const char* file, uint32 line)
{
	return Core_Memory::Malloc(size, alignment, alignmentOffset, allocType, description, file, line);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void* ALBA_CDECL operator new[](size_t size, size_t alignment, size_t alignmentOffset, Core_Memory::TAllocType allocType, const char* description, const char* file, uint32 line)
{
	return Core_Memory::Malloc(size, alignment, alignmentOffset, allocType, description, file, line);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete(void* ptr)
{
	if (ptr)
	{
		Core_Memory::Free(ptr);
	}	
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete[](void* ptr)
{
	if (ptr)
	{
		Core_Memory::Free(ptr);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete(void* ptr, size_t alignment, size_t alignmentOffset, Core_Memory::TAllocType allocType, const char* description, const char* file, uint32 line)
{
	(void)allocType;
	(void)alignment;
	(void)alignmentOffset;
	(void)description;
	(void)file;
	(void)line;

	if (ptr)
	{
		Core_Memory::Free(ptr);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete[](void* ptr, size_t alignment, size_t alignmentOffset, Core_Memory::TAllocType allocType, const char* description, const char* file, uint32 line)
{
	(void)allocType;
	(void)alignment;
	(void)alignmentOffset;
	(void)allocType;
	(void)description;
	(void)file;
	(void)line;

	if (ptr)
	{
		Core_Memory::Free(ptr);
	}
}

//-------------------------------------------------------------------------------------------------
// For EASTL compatibility
//-------------------------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////////////////////
void* ALBA_CDECL operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	(void)pName;
	(void)flags;
	(void)debugFlags;

	return Core_Memory::Malloc(size, 0, 0, Core::AllocType_EASTLContainer, pName, file, line);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void* ALBA_CDECL operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	(void)pName;
	(void)flags;
	(void)debugFlags;

	return Core_Memory::Malloc(size, alignment, alignmentOffset, Core::AllocType_EASTLContainer, pName, file, line);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete[](void* ptr, size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	(void)size;
	(void)pName;
	(void)debugFlags;
	(void)flags;
	(void)debugFlags;
	(void)file;
	(void)line;

	if (ptr)
	{
		Core_Memory::Free(ptr);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete[](void* ptr, size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	(void)size;
	(void)alignment;
	(void)alignmentOffset;
	(void)pName;
	(void)debugFlags;
	(void)flags;
	(void)debugFlags;
	(void)file;
	(void)line;

	if (ptr)
	{
		Core_Memory::Free(ptr);
	}
}