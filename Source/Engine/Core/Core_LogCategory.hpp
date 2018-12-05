#pragma once

#include "Core.hpp"
#include "Core_FixedString.hpp"
#include "Core_Thread.hpp"
#include "Core_Container.hpp"

//-------------------------------------------------------------------------------------------------
// Declare a log category - only needed if you want the log category to be 
// available from multiple .cpp files
//-------------------------------------------------------------------------------------------------
#define ALBA_DECLARE_LOG_CATEGORY(aCategoryName)	namespace LogCategories { inline ::Alba::Core::LogCategory aCategoryName = ::Alba::Core::LogCategory(#aCategoryName); }

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
		enum class LogLevel : uint64
		{
			Verbose,
			Debug,
			Info,
			Warn,
			Error
		};

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
				using CategoryName = const FixedString < 64, OverflowBehavior::Allowed >;

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
				LogLevel			myLogLevel;
				CategoryName		myName;
		};
	}

}