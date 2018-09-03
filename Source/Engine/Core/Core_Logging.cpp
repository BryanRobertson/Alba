#include "Core_Precompile.hpp"
#include "Core_Logging.hpp"
#include "Core_Memory.hpp"

#include <ctime>
#include <iomanip>

#include "Core_PlatformHeader.hpp"

namespace Alba
{
	namespace Core
	{
		/*static*/ UniquePtr<LogManager> LogManager::ourInstance;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ void LogManager::CreateInstance()
		{
			ourInstance.reset(ALBA_NEW(::Alba::Core::AllocationType::CoreDebug, "LogManager") LogManager());
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ void	LogManager::DestroyInstance()
		{
			ourInstance.reset();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ LogManager& LogManager::GetInstance()
		{
			if (!ourInstance)
			{
				// Log manager invalid!
				ALBA_DEBUG_BREAK();

				// Return a static log manager for this case
				// would prefer debug support code to be more robust
				static LogManager aStaticInstance;
				return aStaticInstance;
			}

			return *ourInstance;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		LogManager::LogManager()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void LogManager::LogMessage(const LogCategory& aCategory, LogLevel aLevel, StringView aMessage)
		{
			if (aCategory.GetLogLevel() <= aLevel)
			{
				#if defined(ALBA_PLATFORM_WINDOWS)
				{
					SYSTEMTIME systemTime;
					GetLocalTime(&systemTime);

					typedef FixedString<16> StringType;
					const StringType timeStr
					(
						StringType::CtorSprintf(),
						"[%02d:%02d:%02d.%04d] - ",
						static_cast<int>(systemTime.wHour), 
						static_cast<int>(systemTime.wMinute), 
						static_cast<int>(systemTime.wSecond), 
						static_cast<int>(systemTime.wMilliseconds)
					);

					::OutputDebugString(timeStr.c_str());
					::OutputDebugString(aCategory.GetName().c_str());
					::OutputDebugString(" - ");
					::OutputDebugStringA(aMessage.data());
					::OutputDebugStringA("\n");
				}
				#endif
			}	
		}
	}
}