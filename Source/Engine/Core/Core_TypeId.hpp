#pragma once

#include "Core.hpp"
#include "Core_String.hpp"
#include "Core_StringHash.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	TypeId
		// Desc	:	Associate a type with an integer ID
		//-----------------------------------------------------------------------------------------
		class TypeId
		{
			public:

				//=================================================================================
				// Public Methods
				//=================================================================================
				bool operator== (const TypeId& anOther) const
				{
					return anOther.myValue == myValue;
				}

				bool operator!= (const TypeId& anOther) const
				{
					return anOther.myValue != myValue;
				}

				intptr_t GetValue() const
				{
					return myValue;
				}

			private:

				template <typename TDataType>
				friend TypeId GetTypeId();

				//=================================================================================
				// Private Constructors
				//=================================================================================
				typedef TypeId(*Func)();

				TypeId(Func aFuncAddress)
					: myValue(intptr_t(aFuncAddress))
				{

				}

				//=================================================================================
				// Private Data
				//=================================================================================
				intptr_t myValue;
		};

		template <typename TDataType>
		TypeId GetTypeId()
		{
			return &GetTypeId<std::decay<TDataType>::type>;
		}

		extern ALBA_CORE_API template TypeId GetTypeId<bool>();

		extern ALBA_CORE_API template TypeId GetTypeId<char>();
		extern ALBA_CORE_API template TypeId GetTypeId<unsigned char>();

		extern ALBA_CORE_API template TypeId GetTypeId<short>();
		extern ALBA_CORE_API template TypeId GetTypeId<unsigned short>();

		extern ALBA_CORE_API template TypeId GetTypeId<int>();
		extern ALBA_CORE_API template TypeId GetTypeId<unsigned int>();

		extern ALBA_CORE_API template TypeId GetTypeId<long>();
		extern ALBA_CORE_API template TypeId GetTypeId<unsigned long>();

		extern ALBA_CORE_API template TypeId GetTypeId<long long>();
		extern ALBA_CORE_API template TypeId GetTypeId<unsigned long long>();

		extern ALBA_CORE_API template TypeId GetTypeId<uint16>();
		extern ALBA_CORE_API template TypeId GetTypeId<int16>();

		extern ALBA_CORE_API template TypeId GetTypeId<uint32>();
		extern ALBA_CORE_API template TypeId GetTypeId<int32>();

		extern ALBA_CORE_API template TypeId GetTypeId<uint64>();
		extern ALBA_CORE_API template TypeId GetTypeId<int64>();

		extern ALBA_CORE_API template TypeId GetTypeId<String>();
		extern ALBA_CORE_API template TypeId GetTypeId<StringHash32>();
		extern ALBA_CORE_API template TypeId GetTypeId<StringHash64>();
		extern ALBA_CORE_API template TypeId GetTypeId<NoCaseStringHash32>();
		extern ALBA_CORE_API template TypeId GetTypeId<NoCaseStringHash64>();
	}
}