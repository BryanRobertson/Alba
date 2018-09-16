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
#include "Core_BasicTypes.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////
void* ALBA_CDECL operator new(size_t size)
{
	return Alba::Core::Malloc(size, 0, 0, Alba::Core::TAllocType(Alba::Core::AllocationType::Unknown), "", "", 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete(void* ptr, size_t)
{
	return Alba::Core::Free(ptr);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void* ALBA_CDECL operator new(size_t size, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType, const char* description, const char* file, Alba::uint32 line)
{
	return Alba::Core::Malloc(size, alignment, alignmentOffset, allocType, description, file, line);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void* ALBA_CDECL operator new[](size_t size, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType, const char* description, const char* file, Alba::uint32 line)
{
	return Alba::Core::Malloc(size, alignment, alignmentOffset, allocType, description, file, line);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete(void* ptr)
{
	if (ptr)
	{
		Alba::Core::Free(ptr);
	}	
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete[](void* ptr)
{
	if (ptr)
	{
		Alba::Core::Free(ptr);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete(void* ptr, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType, const char* description, const char* file, Alba::uint32 line)
{
	(void)allocType;
	(void)alignment;
	(void)alignmentOffset;
	(void)description;
	(void)file;
	(void)line;

	if (ptr)
	{
		Alba::Core::Free(ptr);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete[](void* ptr, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType, const char* description, const char* file, Alba::uint32 line)
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
		Alba::Core::Free(ptr);
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

	return Alba::Core::Malloc(size, 0, 0, static_cast<Alba::BasicTypes::uint32>(::Alba::Core::AllocationType::EASTLContainer), pName, file, line);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void* ALBA_CDECL operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	(void)pName;
	(void)flags;
	(void)debugFlags;

	return Alba::Core::Malloc(size, alignment, alignmentOffset, static_cast<Alba::BasicTypes::uint32>(::Alba::Core::AllocationType::EASTLContainer), pName, file, line);
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
		Alba::Core::Free(ptr);
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
		Alba::Core::Free(ptr);
	}
}