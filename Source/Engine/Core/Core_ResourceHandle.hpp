#pragma once

#include "Core.hpp"
#include "Core_ResourceId.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	ResourceHandle
		//-----------------------------------------------------------------------------------------
		template <typename TResourceType, typename TResourceRepository>
		class ResourceHandle
		{
			public:

				//=================================================================================
				// Public Types
				//=================================================================================
				typedef ResourceId<TResourceType>	IdType;
				typedef TResourceType				ResourceType;
				typedef TResourceRepository			RepositoryType;

				typedef ResourceHandle<TResourceType, TResourceRepository> ThisType;

				struct ResourceLock
				{
					ResourceLock(TResourceType* aResource)
						: myResource(aResource)
					{

					}

					~ResourceLock()
					{

					}

					operator TResourceType*()
					{
						return myResource;
					}

					TResourceType* operator->()
					{
						return myResource;
					}

					TResourceType* myResource;
				};

				struct ConstResourceLock
				{
					ConstResourceLock(const TResourceType* aResource)
						: myResource(aResource)
					{

					}

					~ConstResourceLock()
					{

					}

					operator const TResourceType*()
					{
						return myResource;
					}

					const TResourceType* operator->()
					{
						return myResource;
					}

					const TResourceType* myResource;
				};

				//=================================================================================
				// Public Constructors
				//=================================================================================
				ResourceHandle()
					: myResourceId(IdType::InvalidId)
					, myRepository(nullptr)
				{

				}

				explicit ResourceHandle(IdType anId, RepositoryType& aRepository)
					: myResourceId(anId)
					, myRepository(&aRepository)
				{

				}
			
				ResourceHandle(const ThisType& aCopyFrom) = default;
				ResourceHandle(ThisType&& aMoveFrom) = default;

				//=================================================================================
				// Public Methods
				//=================================================================================
				IdType GetId() const
				{
					return myResourceId;
				}

				bool IsValid() const
				{
					return myResourceId.IsValid();
				}

				ConstResourceLock Lock() const
				{
					return ConstResourceLock(myRepository->GetResourcePtr(*this));
				}

				ResourceLock LockMutable()
				{
					return ResourceLock(myRepository->GetResourcePtrMutable(*this));
				}

				void Unlock()
				{
					// Does nothing for now
				}

				bool operator== (const ThisType& aHandle) const
				{
					return myResourceId == aHandle.myResourceId 
						&& myRepository == aHandle.myRepository;
				}

				bool operator< (const ThisType& aHandle) const
				{
					return myResourceId < aHandle.myResourceId;
				}

				bool operator<= (const ThisType& aHandle) const
				{
					return myResourceId <= aHandle.myResourceId;
				}

				bool operator> (const ThisType& aHandle) const
				{
					return myResourceId < aHandle.myResourceId;
				}

				bool operator>= (const ThisType& aHandle) const
				{
					return myResourceId >= aHandle.myResourceId;
				}

				ThisType& operator= (const ThisType& aHandle)
				{
					myResourceId = aHandle.myResourceId;
					myRepository = aHandle.myRepository;

					return *this;
				}

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				TResourceRepository* myRepository;
				IdType				 myResourceId;
		};
	}
}