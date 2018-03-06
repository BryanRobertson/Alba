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

namespace Alba
{
	namespace Core
	{
		//-------------------------------------------------------------------------------------------------
		// Core allocation types
		//-------------------------------------------------------------------------------------------------
		enum class AllocationType
		{
			Unknown				= 0,
			EASTLContainer		= 1,
			CoreDebug			= 2,
			
			Count
		};


		//-------------------------------------------------------------------------------------------------
		// New/Delete macros
		//-------------------------------------------------------------------------------------------------
		#define ALBA_NEW(AllocType, Description)							new(size_t(0), size_t(0), static_cast<uint32>(AllocType), Description, __FILE__, __LINE__)
		#define ALBA_NEW_ARRAY(ClassType, AllocType, Description)			new[](size_t(0), size_t(0), static_cast<uint32>(AllocType), Description, __FILE__, __LINE__)
		#define ALBA_DELETE(Object)											delete Object
		#define ALBA_DELETE_ARRAY(Object)									delete[] Object

		#define ALBA_NEW_ALIGNED(AllocType, Description)					new(size_t(0), size_t(0), size_t(0), static_cast<uint32>(AllocType), Description, __FILE__, __LINE__)
		#define ALBA_NEW_ARRAY_ALIGNED(ClassType, AllocType, Description)	new[](size_t(0), size_t(0), size_t(0), static_cast<uint32>(AllocType), Description, __FILE__, __LINE__)

		#define ALBA_MALLOC(Size, AllocType, Description)					Alba::Core::Malloc(Size, size_t(0), size_t(0), AllocType, Description, __FILE__, __LINE__)
		#define ALBA_REALLOC(Pointer, Size)									Alba::Core::Realloc(Pointer, Size, __FILE__, __LINE__)
		#define ALBA_FREE(Pointer)											Alba::Core::Free(Pointer)

		//-------------------------------------------------------------------------------------------------
		// Malloc/Realloc/Free
		//-------------------------------------------------------------------------------------------------
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
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void* ALBA_CDECL operator new(size_t size, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType, const char* description, const char* file, Alba::Core::uint32 line);

///////////////////////////////////////////////////////////////////////////////////////////////////
void* ALBA_CDECL operator new[](size_t size, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType, const char* description, const char* file, Alba::Core::uint32 line);

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete(void* ptr);

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete[](void* ptr);

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete(void* ptr, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType, const char* description, const char* file, Alba::Core::uint32 line);

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete[](void* ptr, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType, const char* description, const char* file, Alba::Core::uint32 line);

//-------------------------------------------------------------------------------------------------
// For EASTL compatibility
//-------------------------------------------------------------------------------------------------
void* ALBA_CDECL operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void* ALBA_CDECL operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

void ALBA_CDECL operator delete[](void* ptr, size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void ALBA_CDECL operator delete[](void* ptr, size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
