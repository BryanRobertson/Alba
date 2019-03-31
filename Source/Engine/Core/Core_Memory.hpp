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
			TaskSystem			= 3,
			Module				= 4,
			Window				= 6,
			Framework			= 7,
			Renderer			= 8,
			
			Count
		};

		constexpr size_t DefaultAlignment = 8;

		//-------------------------------------------------------------------------------------------------
		// New/Delete macros
		//-------------------------------------------------------------------------------------------------
		#if defined(ALBA_RETAIL_BUILD)
			#define ALBA_NEW(AllocType, Description)							new(size_t(0), ::Alba::Core::DefaultAlignment, static_cast<uint32>(AllocType))
			#define ALBA_NEW_ARRAY(ClassType, AllocType, Description)			new[](size_t(0), ::Alba::Core::DefaultAlignment, static_cast<uint32>(AllocType))
			#define ALBA_NEW_ALIGNED(AllocType, Description)					new(size_t(0), ::Alba::Core::DefaultAlignment, size_t(0), static_cast<uint32>(AllocType))
			#define ALBA_NEW_ARRAY_ALIGNED(ClassType, AllocType, Description)	new[](size_t(0), ::Alba::Core::DefaultAlignment, size_t(0), static_cast<uint32>(AllocType))
			#define ALBA_MALLOC(Size, AllocType, Description)					Alba::Core::Malloc(Size, ::Alba::Core::DefaultAlignment, size_t(0), AllocType)
			#define ALBA_REALLOC(Pointer, Size)									Alba::Core::Realloc(Pointer, Size)
		#else
			#define ALBA_NEW(AllocType, Description)							new(size_t(0), ::Alba::Core::DefaultAlignment, static_cast<uint32>(AllocType), Description, __FILE__, __LINE__)
			#define ALBA_NEW_ARRAY(ClassType, AllocType, Description)			new[](size_t(0), ::Alba::Core::DefaultAlignment, static_cast<uint32>(AllocType), Description, __FILE__, __LINE__)
			#define ALBA_NEW_ALIGNED(AllocType, Description)					new(size_t(0), ::Alba::Core::DefaultAlignment, size_t(0), static_cast<uint32>(AllocType), Description, __FILE__, __LINE__)
			#define ALBA_NEW_ARRAY_ALIGNED(ClassType, AllocType, Description)	new[](size_t(0), ::Alba::Core::DefaultAlignment, size_t(0), static_cast<uint32>(AllocType), Description, __FILE__, __LINE__)
			#define ALBA_MALLOC(Size, AllocType, Description)					Alba::Core::Malloc(Size, ::Alba::Core::DefaultAlignment, size_t(0), AllocType, Description, __FILE__, __LINE__)
			#define ALBA_REALLOC(Pointer, Size)									Alba::Core::Realloc(Pointer, Size, __FILE__, __LINE__)
		#endif

		#define ALBA_DELETE(Object)											delete Object
		#define ALBA_DELETE_ARRAY(Object)									delete[] Object

		#define ALBA_FREE(Pointer)											Alba::Core::Free(Pointer)

		//-------------------------------------------------------------------------------------------------
		// Malloc/Realloc/Free
		//-------------------------------------------------------------------------------------------------
		using TAllocType = uint32;

		#if defined(ALBA_RETAIL_BUILD)
			void* Malloc(size_t size, size_t alignment, size_t alignmentOffset, TAllocType allocType);
			void* Realloc(void* pointer, size_t size);
		#else
			void* Malloc(size_t size, size_t alignment, size_t alignmentOffset, TAllocType allocType, const char* description, const char* file, uint32 line);
			void* Realloc(void* pointer, size_t size, const char* file, uint32 line);
		#endif
		
		void  Free(void* pointer);

		struct AllocatorHelper
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
void* ALBA_CDECL operator new(size_t);

///////////////////////////////////////////////////////////////////////////////////////////////////
void  ALBA_CDECL operator delete(void*, size_t);

#if defined(ALBA_RETAIL_BUILD)

	///////////////////////////////////////////////////////////////////////////////////////////////////
	void* ALBA_CDECL operator new(size_t size, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType);

	///////////////////////////////////////////////////////////////////////////////////////////////////
	void* ALBA_CDECL operator new[](size_t size, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType);

	///////////////////////////////////////////////////////////////////////////////////////////////////
	void ALBA_CDECL operator delete(void* ptr, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType);

	///////////////////////////////////////////////////////////////////////////////////////////////////
	void ALBA_CDECL operator delete[](void* ptr, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType);

#else

	///////////////////////////////////////////////////////////////////////////////////////////////////
	void* ALBA_CDECL operator new(size_t size, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType, const char* description, const char* file, Alba::uint32 line);
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	void* ALBA_CDECL operator new[](size_t size, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType, const char* description, const char* file, Alba::uint32 line);
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	void ALBA_CDECL operator delete(void* ptr, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType, const char* description, const char* file, Alba::uint32 line);
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	void ALBA_CDECL operator delete[](void* ptr, size_t alignment, size_t alignmentOffset, Alba::Core::TAllocType allocType, const char* description, const char* file, Alba::uint32 line);

#endif


///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete(void* ptr);

///////////////////////////////////////////////////////////////////////////////////////////////////
void ALBA_CDECL operator delete[](void* ptr);


//-------------------------------------------------------------------------------------------------
// For EASTL compatibility
//-------------------------------------------------------------------------------------------------
void* ALBA_CDECL operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void* ALBA_CDECL operator new[](size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

void ALBA_CDECL operator delete[](void* ptr, size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void ALBA_CDECL operator delete[](void* ptr, size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
