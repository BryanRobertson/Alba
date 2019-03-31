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

				bool operator< (const TypeId& anOther) const
				{
					return myValue < anOther.myValue;
				}

				bool operator<= (const TypeId& anOther) const
				{
					return myValue <= anOther.myValue;
				}

				bool operator> (const TypeId& anOther) const
				{
					return myValue > anOther.myValue;
				}

				bool operator>= (const TypeId& anOther) const
				{
					return myValue >= anOther.myValue;
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

		extern template TypeId GetTypeId<bool>();

		extern template TypeId GetTypeId<char>();
		extern template TypeId GetTypeId<unsigned char>();

		extern template TypeId GetTypeId<short>();
		extern template TypeId GetTypeId<unsigned short>();

		extern template TypeId GetTypeId<int>();
		extern template TypeId GetTypeId<unsigned int>();

		extern template TypeId GetTypeId<long>();
		extern template TypeId GetTypeId<unsigned long>();

		extern template TypeId GetTypeId<long long>();
		extern template TypeId GetTypeId<unsigned long long>();

		extern template TypeId GetTypeId<uint16>();
		extern template TypeId GetTypeId<int16>();

		extern template TypeId GetTypeId<uint32>();
		extern template TypeId GetTypeId<int32>();

		extern template TypeId GetTypeId<uint64>();
		extern template TypeId GetTypeId<int64>();

		extern template TypeId GetTypeId<String>();
		extern template TypeId GetTypeId<StringHash32>();
		extern template TypeId GetTypeId<StringHash64>();
		extern template TypeId GetTypeId<NoCaseStringHash32>();
		extern template TypeId GetTypeId<NoCaseStringHash64>();
	}
}