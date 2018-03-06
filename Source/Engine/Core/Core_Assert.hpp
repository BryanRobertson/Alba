#pragma once

//-------------------------------------------------------------------------------------------------
// Name      : Core_Assert.hpp
// Desc      : Debug assert macros
// Author    : Bryan Robertson
// Date      : 2018/02/28
//-------------------------------------------------------------------------------------------------
#include "Core_Config.hpp"
#include "Core_BasicTypes.hpp"
#include "Core_LogCategory.hpp"
#include <cstdlib>

namespace Alba
{
	namespace Core
	{
		ALBA_DECLARE_LOG_CATEGORY(Critical);

		//------------------------------------------------------------------------------------------------ -
		// Name : EAssertFailBehaviour
		// Desc : Enum for different behaviours to be triggered on assertion failure
		//-------------------------------------------------------------------------------------------------
		enum class AssertFailBehaviour
		{
			DebugBreak,
			Abort
		};

		//-------------------------------------------------------------------------------------------------
		// Name : AlbaAssertHandler
		// Desc : Function pointer for functions that handle assertion failures
		//-------------------------------------------------------------------------------------------------
		typedef AssertFailBehaviour(*AlbaAssertHandler)(const char* aConditionStr, const char* anErrorMessage, const char* aFile, const uint32 aLine);

		//-------------------------------------------------------------------------------------------------
		// Default assert handler function
		//-------------------------------------------------------------------------------------------------
		ALBA_CORE_API AssertFailBehaviour DefaultAssertHandler(const char* aConditionStr, const char* anErrorMessage, const char* aFile, const uint32 aLine);

		//-------------------------------------------------------------------------------------------------
		// AssertHandlerWrapper
		//-------------------------------------------------------------------------------------------------
		struct ALBA_CORE_API AssertHandlerWrapper
		{
			static AlbaAssertHandler ourGlobalAssertHandler;
		};

		//-------------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------
		namespace AssertInternal
		{
			struct StringLiteralWrapper
			{
				StringLiteralWrapper(const char* aStr)
					: myStr(aStr)
				{

				}

				const char* c_str() const { return myStr;  }

				const char* myStr;
			};

			inline StringLiteralWrapper FormatAssertMessage()
			{
				return StringLiteralWrapper("");
			}

			inline StringLiteralWrapper FormatAssertMessage(const char* aFormat)
			{
				return StringLiteralWrapper(aFormat);
			}

			template <typename... TArgs>
			inline FixedString<256> FormatAssertMessage(const char* aFormat, TArgs&&... someArgs)
			{
				return FixedString<256>(FixedString<256>::CtorSprintf(), aFormat, std::forward<TArgs>(someArgs)...);
			}
		}
	}
}

#if defined(ALBA_COMPILER_VISUALSTUDIO)
	#define ALBA_DEBUG_BREAK()	__debugbreak()	
	#define ALBA_ABORT() std::abort()
#else
	#define ALBA_DEBUG_BREAK()
	#define ALBA_ABORT()
#endif

#if defined(ALBA_DEBUG_ASSERTS_ENABLED)
	#define ALBA_ASSERT_FAILED(anAssertCond, ...)											   \
	{																						   \
		if (::Alba::Core::AssertHandlerWrapper::ourGlobalAssertHandler						   \
				(	#anAssertCond, 															   \
					::Alba::Core::AssertInternal::FormatAssertMessage(__VA_ARGS__).c_str(),    \
					__FILE__, 																   \
					__LINE__																   \
				)																			   \
				== ::Alba::Core::AssertFailBehaviour::DebugBreak							   \
			)																				   \
		{																					   \
			 ALBA_DEBUG_BREAK();															   \
		}																					   \
		else																				   \
		{																					   \
			std::abort();																	   \
		}																					   \
	}																						   
	
	#define ALBA_ASSERT(anAssertCond, ...) do { if (!(anAssertCond)) { ALBA_ASSERT_FAILED(anAssertCond, __VA_ARGS__); }  } while (0)

	#define ALBA_SET_ASSERTHANDLER(anAssertHandler)	::Alba::Core::AssertHandlerWrapper::ourGlobalAssertHandler = anAssertHandler
	#define ALBA_CLEAR_ASSERTHANDLER()	::Alba::Core::AssertHandlerWrapper::ourGlobalAssertHandler = &::Alba::Core::DefaultAssertHandler;
#else
	#define ALBA_ASSERT_FAILED(anAssertCond, ...)	
	#define ALBA_ASSERT(anAssertCond, ...)

	#define ALBA_SET_ASSERTHANDLER(anAssertHandler)
	#define ALBA_CLEAR_ASSERTHANDLER()
#endif

