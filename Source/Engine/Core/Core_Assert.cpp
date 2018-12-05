#include "Core_Precompile.hpp"
#include "Core_Assert.hpp"
#include "Core_Logging.hpp"

namespace Alba
{
	namespace Core
	{
		#if defined(ALBA_DEBUG_ASSERTS_ENABLED)

		//-------------------------------------------------------------------------------------------------
		// Global assert handler 
		//-------------------------------------------------------------------------------------------------
		ALBA_CORE_API AlbaAssertHandler theGlobalAssertHandler = &DefaultAssertHandler;

		//-------------------------------------------------------------------------------------------------
		// Default assert handler
		//-------------------------------------------------------------------------------------------------
		AssertFailBehaviour DefaultAssertHandler(const char* aCondition, const char* anErrorMessage, const char* aFile, const uint32 aLine)
		{
			#ifdef ALBA_PLATFORM_WINDOWS
			{
				if ( anErrorMessage && anErrorMessage[0] != '\0' )
				{
					ALBA_LOG
					(
						Critical,
						LogLevel::Error,
						"%s(%u): Assertion Failed ( %s ) - \"%s\"",
						aFile, aLine, aCondition, anErrorMessage
					);
				}
				else
				{
					ALBA_LOG
					(
						Critical,
						LogLevel::Error,
						"%s(%u): Assertion Failed ( %s )",
						aFile, aLine, aCondition
					);
				}
			}
			#else
				#pragma error("Not Implemented");
			#endif

			return AssertFailBehaviour::DebugBreak;
		}

		//-------------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------------
		/*static*/ AlbaAssertHandler AssertHandlerWrapper::ourGlobalAssertHandler = &DefaultAssertHandler;
		#endif
	}
}