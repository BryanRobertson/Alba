#include "Core_Precompile.hpp"
#include "Core_Logging.hpp"
#include "Core_Memory.hpp"
#include "Core_StringView.hpp"

#include <ctime>
#include <iomanip>

#include "Core_PlatformHeader.hpp"
#include "Core_ConsoleModule.hpp"

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

					const auto logStr = Core::FormatString<256>
					(
						"[%02d:%02d:%02d.%04d] - %s - %s",
						static_cast<int>(systemTime.wHour), 
						static_cast<int>(systemTime.wMinute), 
						static_cast<int>(systemTime.wSecond), 
						static_cast<int>(systemTime.wMilliseconds),
						aCategory.GetName().c_str(), 
						aMessage.data()
					);

					LogRaw(aLevel, StringView(logStr.data(), logStr.size()));
				}
				#else
					#pragma error("Not Implemented");
				#endif
			}	
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void LogManager::LogRaw(LogLevel aLevel, StringView aRawLogMessage)
		{
			//-----------------------------------------------------------------------------------------
			// Print to debugger output window
			//-----------------------------------------------------------------------------------------
			#if defined(ALBA_PLATFORM_WINDOWS) && !defined(ALBA_RETAIL_BUILD)
			{
				if (::IsDebuggerPresent())
				{
					::OutputDebugString(aRawLogMessage.data());
					::OutputDebugString("\n");
				}
			}
			#endif

			//-----------------------------------------------------------------------------------------
			// Print to console
			//-----------------------------------------------------------------------------------------
			if (ConsoleModule::IsLoaded())
			{
				if (aLevel >= LogLevel::Warn)
				{
					const ConsoleMessageType messageType = aLevel == LogLevel::Warn ? ConsoleMessageType::Warning : ConsoleMessageType::Error;

					ConsoleModule& consoleModule = ConsoleModule::Get();
					Console& console = consoleModule.GetConsole();

					console.Print(messageType, aRawLogMessage);
				}
			}
		}
	}
}