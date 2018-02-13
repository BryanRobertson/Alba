#pragma once

//-------------------------------------------------------------------------------------------------
// Name      : Core_Memory.hpp
// Desc      : Override of new/delete, etc
// Author    : Bryan Robertson
// Date      : 2016/11/20
//-------------------------------------------------------------------------------------------------

#include "Core_API.hpp"
#include "Core_Config.hpp"
#include "Core_BasicTypes.hpp"

#include <new>

namespace Core
{
	//-------------------------------------------------------------------------------------------------
	// Core allocation types
	//-------------------------------------------------------------------------------------------------
	enum AllocationType
	{
		AllocType_Unknown			= 0,
		AllocType_EASTLContainer	= 1,
		AllocType_Count
	};
}

//-------------------------------------------------------------------------------------------------
// New/Delete macros
//-------------------------------------------------------------------------------------------------
#define ALBA_NEW(AllocType, Description)							new(size_t(0), size_t(0), AllocType, Description, __FILE__, __LINE__)
#define ALBA_NEWArray(ClassType, AllocType, Description)			new[](size_t(0), size_t(0), AllocType, Description, __FILE__, __LINE__)
#define ALBA_DELETE(Object)											delete Object
#define ALBA_DELETE_ARRAY(Object)									delete[] Object

#define ALBA_NEW_ALIGNED(AllocType, Description)					new(size_t(0), size_t(0), AllocType, Description, __FILE__, __LINE__)
#define ALBA_NEW_ALIGNEDArray(ClassType, AllocType, Description)	new[](size_t(0), size_t(0), AllocType, Description, __FILE__, __LINE__)

#define ALBA_MALLOC(Size, AllocType, Description)					Core_Memory::Malloc(Size, AllocType, Description, __FILE__, __LINE__)
#define ALBA_REALLOC(Pointer, Size)									Core_Memory::Realloc(Pointer, Size, __FILE__, __LINE__)
#define ALBA_FREE(Pointer)											Core_Memory::Free(Pointer)

//-------------------------------------------------------------------------------------------------
// Malloc/Realloc/Free
//-------------------------------------------------------------------------------------------------
namespace Core_Memory
{
	using namespace Core_BasicTypes;

	typedef uint32 TAllocType;

	ALBA_CORE_API void* Malloc(size_t size, size_t alignment, size_t alignmentOffset, TAllocType allocType, const char* description, const char* file, uint32 line);
	ALBA_CORE_API void* Realloc(void* pointer, size_t size, const char* file, uint32 line);
	ALBA_CORE_API void  Free(void* pointer);

	 struct ALBA_CORE_API AllocatorHelper
	{
		template <typename T>
		AllocatorHelper& Delete(T* ptr)
		{
			if (ptr)
			{
				ptr->~T();
				Free(ptr);
			}
		}

		template <typename T>
		AllocatorHelper& DeleteArray(T* ptr)
		{
			if (ptr)
			{
				ptr->~T();
				Free(ptr);
			}
		}
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void* ALBA_CDECL operator new(size_t size, size_t alignment, size_t alignmentOffset, Core_Memory::TAllocType allocType, const char* description, const char* file, uint32 line);

///////////////////////////////////////////////////////////////////////////////////////////////////
void* ALBA_CDECL operator new[](size_t size, size_t alignment, size_t alignmentOffset, Core_Memory::TAllocType allocType, const char* description, const char* file, uint32 line);

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete(void* ptr);

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete[](void* ptr);

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete(void* ptr, size_t alignment, size_t alignmentOffset, Core_Memory::TAllocType allocType, const char* description, const char* file, uint32 line);

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete[](void* ptr, size_t alignment, size_t alignmentOffset, Core_Memory::TAllocType allocType, const char* description, const char* file, uint32 line);

//-------------------------------------------------------------------------------------------------
// For EASTL compatibility
//-------------------------------------------------------------------------------------------------
void* ALBA_CDECL operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void* ALBA_CDECL operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

void ALBA_CDECL operator delete[](void* ptr, size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void ALBA_CDECL operator delete[](void* ptr, size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line);