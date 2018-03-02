#include "Core_Precompile.hpp"
#include "Core_StringHash.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		StringHash32::StringHash32()
		{
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		StringHash32::StringHash32(uint32 aHash)
			: Super(aHash)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		StringHash64::StringHash64()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		StringHash64::StringHash64(uint64 aHash)
			: Super(aHash)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		NoCaseStringHash32::NoCaseStringHash32()
		{
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		NoCaseStringHash32::NoCaseStringHash32(uint32 aHash)
			: Super(aHash)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		NoCaseStringHash64::NoCaseStringHash64()
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		NoCaseStringHash64::NoCaseStringHash64(uint64 aHash)
			: Super(aHash)
		{

		}
	}
}