#pragma once

#include "Core_API.hpp"
#include "Core_FixedString.hpp"
#include "Core_Thread.hpp"
#include "Core_Container.hpp"

//-------------------------------------------------------------------------------------------------
// Name      : Core_LogCategory.hpp
// Desc      : Log categorisation for filtered log output
// Author    : Bryan Robertson
// Date      : 2017/03/20
//-------------------------------------------------------------------------------------------------
namespace Alba
{
	namespace Core
	{
		//-------------------------------------------------------------------------------------------------
		// Name		: LogLevel
		// Desc		: Log level
		//-------------------------------------------------------------------------------------------------
		enum class LogLevel : uint8
		{
			Verbose,
			Debug,
			Info,
			Warn,
			Error
		};

		#define CORE_DECLARE_LOG_CATEGORY(aCategoryName)		namespace LogCategory {	extern LogCategory aCategoryName;					}
		#define CORE_IMPLEMENT_LOG_CATEGORY(aCategoryName)		namespace LogCategory {	LogCategory aCategoryName(#aCategoryName);			}

		//-------------------------------------------------------------------------------------------------
		// Name      : Core::LogCategory.hpp
		// Desc      : Categorised log
		// Author    : Bryan Robertson
		// Date      : 2016/12/22
		//-------------------------------------------------------------------------------------------------
		class ALBA_CORE_API LogCategory
		{
			public:

				//===============================================================================================
				// Public Types
				//===============================================================================================
				typedef const FixedString < 64, OverflowBehavior::Allowed > CategoryName;

				//===============================================================================================
				// Public Constructors
				//===============================================================================================
				LogCategory(const CategoryName&& aCategoryName);

				//===============================================================================================
				// Public Methods
				//===============================================================================================
				void				SetLogLevel(LogLevel aLevel);
				LogLevel			GetLogLevel() const;

				const CategoryName& GetName() const						{ return myName;  }

			private:

				//===============================================================================================
				// Private Data
				//===============================================================================================
				Atomic<LogLevel>		myLogLevel;
				CategoryName			myName;
		};

	}

}