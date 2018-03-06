#include "Core_Precompile.hpp"
#include "Core_Logging.hpp"
#include "Core_Memory.hpp"

#include <ctime>
#include <iomanip>

#if defined(ALBA_PLATFORM_WINDOWS)
	#pragma warning( push, 3 )  
		#include <Windows.h>
	#pragma warning( pop ) 
	//#include <debugapi.h>
#endif

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
		void LogManager::LogMessage(const LogCategory& aCategory, LogLevel aLevel, const char* aMessage)
		{
			if (aCategory.GetLogLevel() <= aLevel)
			{
				#if defined(ALBA_PLATFORM_WINDOWS)
				{
					/*
					const auto now = std::chrono::system_clock::to_time_t(Core_Chrono::system_clock::now());
					const auto nowLocalTime = *std::localtime(&now);
		
					Core_FixedString<256>::CtorSprintf cs;
					Core_FixedString<256> str
					(
						cs,
						"%s: %s : %s\n", 
						std::put_time(&nowLocalTime, "Y-m-d H:M:S"),
						aCategory.GetName(),
						aMessage
					);
					*/

					::OutputDebugStringA(aMessage);
					::OutputDebugStringA("\n");
				}
				#endif
			}	
		}
	}
}