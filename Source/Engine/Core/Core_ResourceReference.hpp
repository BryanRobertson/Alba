#pragma once

#include "Core_ResourceHandle.hpp"
#include "Core_SharedPtr.hpp"

namespace Alba
{
	namespace Core
	{
		template <typename TResourceType, typename TRepositoryType>
		class ResourceWeakReference;

		//-----------------------------------------------------------------------------------------
		// Name	:	ResourceReference
		// Desc	:	Reference counted handle to a resource. Automatically unloads resource
		//			when the last copy is deleted
		//-----------------------------------------------------------------------------------------
		template <typename TResourceType, typename TRepositoryType>
		class ResourceReference
		{
			public:

				friend class ResourceWeakReference<TResourceType, TRepositoryType>;

				template <typename TDerived, typename TResourceType>
				friend class ResourceRepository;

				//=================================================================================
				// Public Types
				//=================================================================================
				typedef ResourceHandle<TResourceType, TRepositoryType> HandleType;

				//=================================================================================
				// Public Constructors
				//=================================================================================
				ResourceReference() = default;
				ResourceReference(const ResourceReference<TResourceType, TRepositoryType>& aCopyFrom) = default;
				ResourceReference(ResourceReference<TResourceType, TRepositoryType>&& aMoveFrom) = default;

				//=================================================================================
				// Public Methods
				//=================================================================================
				const TResourceType& Get() const
				{
					return *myResourcePtr;
				}

				TResourceType& GetMutable()
				{
					return *myResourcePtr;
				}

				bool IsValid() const
				{
					return myResourcePtr != nullptr;
				}

				void Reset()
				{
					myResourcePtr.clear();
				}

				bool operator== (const ResourceReference<TResourceType, TRepositoryType>& aReference) const
				{
					return myResourcePtr == aReference.myResourcePtr;
				}

				bool operator< (const ResourceReference<TResourceType, TRepositoryType>& aReference) const
				{
					return myResourcePtr.get() < aReference.myResourcePtr.get();
				}

				bool operator> (const ResourceReference<TResourceType, TRepositoryType>& aReference) const
				{
					return myResourcePtr.get() > aReference.myResourcePtr.get();
				}

				bool operator= (const ResourceReference<TResourceType, TRepositoryType>& aReference)
				{
					myResourcePtr = aReference.myResourcePtr;
				}

			private:

				//=================================================================================
				// Private Constructors
				//=================================================================================
				ResourceReference(SharedPtr<TResourceType> aResourcePtr)
					: myResourcePtr(std::move(aResourcePtr))
				{
				
				}

				//=================================================================================
				// Private Data
				//=================================================================================
				SharedPtr<TResourceType> myResourcePtr;
		};

		//-----------------------------------------------------------------------------------------
		// Name	:	ResourceWeakReference
		// Desc :	Weak reference to a resource (does not keep the resource alive)
		//-----------------------------------------------------------------------------------------
		template <typename TResourceType, typename TRepositoryType>
		class ResourceWeakReference
		{
			public:

				template <typename TDerived, typename TResourceType>
				friend class ResourceRepository;

				//=================================================================================
				// Public Constructors
				//=================================================================================
				ResourceWeakReference() = default;
				ResourceWeakReference(const ResourceWeakReference<TResourceType, TRepositoryType>& aCopyFrom) = default;
				ResourceWeakReference(ResourceWeakReference<TResourceType, TRepositoryType>&& aMoveFrom) = default;

				ResourceWeakReference(const ResourceReference<TResourceType, TRepositoryType>& aReference)
				{
					myResourcePtr = aReference.myResourcePtr;
				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				ResourceReference<TResourceType, TRepositoryType> Lock()
				{
					return ResourceReference<TResourceType, TRepositoryType>(myResourcePtr.lock());
				}

				bool operator== (const ResourceWeakReference<TResourceType, TRepositoryType>& aReference) const
				{
					return myResourcePtr == aReference.myResourcePtr;
				}

				bool operator< (const ResourceWeakReference<TResourceType, TRepositoryType>& aReference) const
				{
					return myResourcePtr.get() < aReference.myResourcePtr.get();
				}

				bool operator> (const ResourceWeakReference<TResourceType, TRepositoryType>& aReference) const
				{
					return myResourcePtr.get() > aReference.myResourcePtr.get();
				}

				bool operator= (const ResourceWeakReference<TResourceType, TRepositoryType>& aReference)
				{
					myResourcePtr = aReference.myResourcePtr;
				}

			private:

				//==================================================================================
				// Private Data
				//==================================================================================
				WeakPtr<TResourceType> myResourcePtr;
		};
	}
}