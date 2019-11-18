#include "Core_Precompile.hpp"
#include "Core_ThreadId.hpp"
#include "Core_PlatformHeader.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		/*static*/ const ThreadId ThreadId::Invalid;

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------
		ThreadId GetCurrentThreadId()
		{
			const int32 value = ::GetCurrentThreadId();
			return ThreadId{ value };
		}
	}
}