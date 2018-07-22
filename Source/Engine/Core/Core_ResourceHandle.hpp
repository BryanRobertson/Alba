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

				explicit ResourceHandle(const ThisType& aCopyFrom) = default;
				explicit ResourceHandle(ThisType&& aMoveFrom) = default;

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

				const ResourceType* Lock() const
				{
					return myRepository->GetResourcePtr(myResourceId);
				}

				ResourceType* LockMutable()
				{
					return myRepository->GetResourcePtrMutable(myResourceId);
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