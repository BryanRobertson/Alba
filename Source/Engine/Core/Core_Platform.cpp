#include "Core_Precompile.hpp"
#include "Core_Platform.hpp"
#include "Core_PlatformHeader.hpp"

namespace Alba
{
	namespace Core
	{
		#if defined(ALBA_PLATFORM_WINDOWS)

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			String GetLastErrorString()
			{
				int errorCode = GetLastError();

				LPVOID messageBuffer = nullptr;
				const DWORD bufferLength = FormatMessage
				(
					FORMAT_MESSAGE_ALLOCATE_BUFFER
					| FORMAT_MESSAGE_FROM_SYSTEM
					| FORMAT_MESSAGE_IGNORE_INSERTS,
					nullptr,
					errorCode,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPTSTR)&messageBuffer,
					0, 
					nullptr
				);

				if (bufferLength)
				{
					LPCSTR messageString = (LPCSTR)messageBuffer;
					String result(messageString, messageString + bufferLength);

					LocalFree(messageBuffer);

					return result;
				}

				return String();
			}
		#endif	
	}
}