#include "Core_Precompile.hpp"
#include "Core_LogCategory.hpp"

namespace Alba
{
	namespace Core
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////
		LogCategory::LogCategory(const LogCategory::CategoryName&& aCategoryName)
			: myName(std::move(aCategoryName))
			, myLogLevel(LogLevel::Info)
		{

		}

		///////////////////////////////////////////////////////////////////////////////////////////////////
		void LogCategory::SetLogLevel(LogLevel aLevel)
		{
			// TODO: Something more precise than operator=
			myLogLevel = aLevel;
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////
		LogLevel LogCategory::GetLogLevel() const
		{
			return myLogLevel;
		}
	}
}