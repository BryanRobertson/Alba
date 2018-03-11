#pragma once

//------------------------------------------------------------------------------------------------
// Name      : Core_AnyDictionary.hpp
// Author    : Bryan Robertson
// Date      : 2018/03/07
//------------------------------------------------------------------------------------------------
#include "Core.hpp"
#include "Core_Any.hpp"
#include "Core_VectorMap.hpp"
#include "Core_TypeId.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	AnyDictionary
		// Desc	:   Class that can store multiple objects of different types simultaneously
		//			analogous to a dictionary of type -> value
		//-----------------------------------------------------------------------------------------
		class AnyDictionary
		{
			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				AnyDictionary();

				//=================================================================================
				// Public Methods
				//=================================================================================
				template <typename TDataType>
				void Set(const TDataType& aTypedValue)
				{
					const TypeId typeId = GetTypeId<TDataType>();
					auto itr = myData.find(typeId);

					if (itr != myData.end())
					{
						itr->second = aTypedValue;
					}
					else
					{
						myData.insert(MakePair(typeId, MakeAny(aTypedValue)));
					}
				}

				template <typename TDataType>
				void Set(const TDataType&& aTypedValue)
				{
					const TypeId typeId = GetTypeId<TDataType>();
					auto itr = myData.find(typeId);

					if (itr != myData.end())
					{
						itr->second = std::move(aTypedValue);
					}
					else
					{
						myData.insert(MakePair(typeId, MakeAny(std::move(aTypedValue))));
					}
				}

				template <typename TDataType>
				bool Has(const TDataType& aTypedValue)
				{
					const TypeId typeId = GetTypeId<TDataType>();
					return myData.find(typeId) != myData.end();
				}

				template <typename TDataType>
				const TDataType& Get() const
				{
					const TypeId typeId = GetTypeId<TDataType>();
					auto itr = myData.find(typeId);

					ALBA_ASSERT(itr != myData.end(), "Get<TDataType> failed - use Has<TDataType>() first!");
					return itr->second.To<TDataType>();
				}

				template <typename TDataType>
				TDataType& GetMutable()
				{
					const TypeId typeId = GetTypeId<TDataType>();
					auto itr = myData.find(typeId);

					ALBA_ASSERT(itr != myData.end(), "Get<TDataType> failed - use Has<TDataType>() first!");
					return itr->second.To<TDataType>();
				}

			private:

				//=================================================================================
				// Private Types
				//=================================================================================
				typedef VectorMap<TypeId, Any> DictionaryType;

				//=================================================================================
				// Private Data
				//=================================================================================
				DictionaryType	myData;
		};
	}
}