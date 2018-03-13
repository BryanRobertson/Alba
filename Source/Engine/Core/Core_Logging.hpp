#pragma once

#include "Core.hpp"
#include "Core_Time.hpp"
#include "Core_LogCategory.hpp"
#include "Core_UniquePtr.hpp"
#include "Core_StringUtils.hpp"

#ifdef ALBA_DEBUG_LOGGING_ENABLED
	#define ALBA_GET_LOG_MANAGER()	::Alba::Core::LogManager::GetInstance()

	#define ALBA_LOG(aLogCategory, aLevel, aFormat, ...)								\
	{																					\
		ALBA_GET_LOG_MANAGER().LogMessage												\
		(																				\
			aLogCategory,																\
			aLevel,																		\
			::Alba::Core::FormatString<256>(aFormat, __VA_ARGS__).c_str()				\
		);																				\
	}

	#define ALBA_LOG_VERBOSE(aLogCategory, aFormat, ...)	ALBA_LOG(aLogCategory, ::Alba::Core::LogLevel::Verbose, aFormat, __VA_ARGS__)
	#define ALBA_LOG_DEBUG(aLogCategory, aFormat, ...)		ALBA_LOG(aLogCategory, ::Alba::Core::LogLevel::Debug, aFormat, __VA_ARGS__)
	#define ALBA_LOG_INFO(aLogCategory, aFormat, ...)		ALBA_LOG(aLogCategory, ::Alba::Core::LogLevel::Info, aFormat, __VA_ARGS__)
	#define ALBA_LOG_WARNING(aLogCategory, aFormat, ...)	ALBA_LOG(aLogCategory, ::Alba::Core::LogLevel::Warning, aFormat, __VA_ARGS__)
	#define ALBA_LOG_ERROR(aLogCategory, aFormat, ...)		ALBA_LOG(aLogCategory, ::Alba::Core::LogLevel::Error, aFormat, __VA_ARGS__)

#else

	#define ALBA_LOG(aLogCategory, aLevel, aFormat, ...)
	#define ALBA_LOG_VERBOSE(aLogCategory, aFormat, ...)
	#define ALBA_LOG_DEBUG(aLogCategory, aFormat, ...)
	#define ALBA_LOG_INFO(aLogCategory, aFormat, ...)
	#define ALBA_LOG_WARNING(aLogCategory, aFormat, ...)
	#define ALBA_LOG_ERROR(aLogCategory, aFormat, ...)

#endif

//-------------------------------------------------------------------------------------------------
// Name      : Core_Logging.hpp
// Desc      : Logging functionality
// Author    : Bryan Robertson
// Date      : 2016/12/20
//-------------------------------------------------------------------------------------------------
namespace Alba
{
	namespace Core
	{
		//-------------------------------------------------------------------------------------------------
		// Name	:	LogManager
		//-------------------------------------------------------------------------------------------------
		class ALBA_CORE_API LogManager final
		{
			public:

				//=========================================================================================
				// Public Constructor
				//=========================================================================================
				LogManager();

				//=========================================================================================
				// Public Methods
				//=========================================================================================
				void LogMessage(const LogCategory& aCategory, LogLevel aLevel, const char* aMessage);

				//=========================================================================================
				// Public Static Methods
				//=========================================================================================
				static void			CreateInstance();
				static void			DestroyInstance();
				static LogManager&	GetInstance();

			private:

				//=========================================================================================
				// Private Static Darta
				//=========================================================================================
				static UniquePtr<LogManager> ourInstance;
		};
	}
}