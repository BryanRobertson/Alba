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
	#if defined(ALBA_RETAIL_BUILD)
		return Alba::Core::Malloc(size, 0, 0, Alba::Core::TAllocType(Alba::Core::AllocationType::Unknown));
	#else
		return Alba::Core::Malloc(size, 0, 0, Alba::Core::TAllocType(Alba::Core::AllocationType::Unknown), "", "", 0);
	#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete(void* ptr, size_t)
{
	return Alba::Core::Free(ptr);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(ALBA_RETAIL_BUILD)
	void* ALBA_CDECL operator new(size_t size, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType)
#else
	void* ALBA_CDECL operator new(size_t size, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType, const char* description, const char* file, Alba::uint32 line)
#endif
{
	#if defined(ALBA_RETAIL_BUILD)
		return Alba::Core::Malloc(size, alignment, alignmentOffset, allocType);
	#else
		return Alba::Core::Malloc(size, alignment, alignmentOffset, allocType, description, file, line);
	#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(ALBA_RETAIL_BUILD)
	void* ALBA_CDECL operator new[](size_t size, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType)
#else
	void* ALBA_CDECL operator new[](size_t size, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType, const char* description, const char* file, Alba::uint32 line)
#endif
{
	#if defined(ALBA_RETAIL_BUILD)
		return Alba::Core::Malloc(size, alignment, alignmentOffset, allocType);
	#else
		return Alba::Core::Malloc(size, alignment, alignmentOffset, allocType, description, file, line);
	#endif
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
#if defined(ALBA_RETAIL_BUILD)
	void ALBA_CDECL operator delete(void* ptr, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType)
#else
	void ALBA_CDECL operator delete(void* ptr, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType, const char* description, const char* file, Alba::uint32 line)
#endif
{
	(void)allocType;
	(void)alignment;
	(void)alignmentOffset;

	#if !defined(ALBA_RETAIL_BUILD)
		(void)description;
		(void)file;
		(void)line;
	#endif

	if (ptr)
	{
		Alba::Core::Free(ptr);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(ALBA_RETAIL_BUILD)
	void ALBA_CDECL operator delete[](void* ptr, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType)
#else
	void ALBA_CDECL operator delete[](void* ptr, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType, const char* description, const char* file, Alba::uint32 line)
#endif
{
	(void)allocType;
	(void)alignment;
	(void)alignmentOffset;
	(void)allocType;

	#if !defined(ALBA_RETAIL_BUILD)
		(void)description;
		(void)file;
		(void)line;
	#endif

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
	(void)file;
	(void)line;

	#if defined(ALBA_RETAIL_BUILD)
		return Alba::Core::Malloc(size, 0, 0, static_cast<Alba::BasicTypes::uint32>(::Alba::Core::AllocationType::EASTLContainer));
	#else
		return Alba::Core::Malloc(size, 0, 0, static_cast<Alba::BasicTypes::uint32>(::Alba::Core::AllocationType::EASTLContainer), pName, file, line);
	#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void* ALBA_CDECL operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	(void)pName;
	(void)flags;
	(void)debugFlags;
	(void)file;
	(void)line;

	#if defined(ALBA_RETAIL_BUILD)
		return Alba::Core::Malloc(size, alignment, alignmentOffset, static_cast<Alba::BasicTypes::uint32>(::Alba::Core::AllocationType::EASTLContainer));
	#else
		return Alba::Core::Malloc(size, alignment, alignmentOffset, static_cast<Alba::BasicTypes::uint32>(::Alba::Core::AllocationType::EASTLContainer), pName, file, line);
	#endif
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