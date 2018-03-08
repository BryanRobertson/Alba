#include "Core_Precompile.hpp"
#include "Core_TypeId.hpp"
namespace Alba
{
	namespace Core
	{
		template TypeId GetTypeId<bool>();

		template TypeId GetTypeId<char>();
		template TypeId GetTypeId<unsigned char>();

		template TypeId GetTypeId<short>();
		template TypeId GetTypeId<unsigned short>();

		template TypeId GetTypeId<int>();
		template TypeId GetTypeId<unsigned int>();

		template TypeId GetTypeId<long>();
		template TypeId GetTypeId<unsigned long>();

		template TypeId GetTypeId<long long>();
		template TypeId GetTypeId<unsigned long long>();

		template TypeId GetTypeId<uint16>();
		template TypeId GetTypeId<int16>();

		template TypeId GetTypeId<uint32>();
		template TypeId GetTypeId<int32>();

		template TypeId GetTypeId<uint64>();
		template TypeId GetTypeId<int64>();

		template TypeId GetTypeId<String>();
		template TypeId GetTypeId<StringHash32>();
		template TypeId GetTypeId<StringHash64>();
		template TypeId GetTypeId<NoCaseStringHash32>();
		template TypeId GetTypeId<NoCaseStringHash64>();
	}
}
