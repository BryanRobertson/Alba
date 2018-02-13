#pragma once

#include "Core_API.hpp"
#include "Core_FixedString.hpp"
#include "Core_Thread.hpp"

//-------------------------------------------------------------------------------------------------
// Name      : Core_LogCategory.hpp
// Desc      : Log categorisation for filtered log output
// Author    : Bryan Robertson
// Date      : 2017/03/20
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Name		: Core_LogLevel
// Desc		: Log level
//-------------------------------------------------------------------------------------------------
enum class Core_LogLevel : uint8
{
	Verbose,
	Debug,
	Info,
	Warn,
	Error
};

#define CORE_DECLARE_LOG_CATEGORY(aCategoryName)		namespace LogCategory {	extern Core_LogCategory aCategoryName;					}
#define CORE_IMPLEMENT_LOG_CATEGORY(aCategoryName)		namespace LogCategory {	Core_LogCategory aCategoryName(#aCategoryName);			}

//-------------------------------------------------------------------------------------------------
// Name      : Core_LogCategory.hpp
// Desc      : Categorised log
// Author    : Bryan Robertson
// Date      : 2016/12/22
//-------------------------------------------------------------------------------------------------
class ALBA_CORE_API Core_LogCategory
{
	public:

		//===============================================================================================
		// Public Types
		//===============================================================================================
		typedef const Core_FixedString<64, Core_OverflowBehavior::Allowed> CategoryName;

		//===============================================================================================
		// Public Constructors
		//===============================================================================================
		Core_LogCategory(const CategoryName&& aCategoryName);

		//===============================================================================================
		// Public Methods
		//===============================================================================================
		void			SetLogLevel(Core_LogLevel aLevel);
		Core_LogLevel	GetLogLevel() const;

		const CategoryName& GetName() const						{ return myName;  }

	private:

		//===============================================================================================
		// Private Data
		//===============================================================================================
		Core_Atomic<Core_LogLevel>	myLogLevel;
		CategoryName				myName;
};