#pragma once

#include "Core.hpp"
#include "Core_ResourceId.hpp"
#include "Core_ResourceHandle.hpp"

namespace Alba
{
	namespace Core
	{
		//-----------------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------------
		enum class ResourceState : uint32
		{
			Invalid,
			Unloaded,
			Loading,
			Loaded
		};

		//-----------------------------------------------------------------------------------------------------
		// Name :	Resource<T>
		// Desc	:	Base class for all resource types
		//-----------------------------------------------------------------------------------------------------
		template <typename TDerived>
		class Resource
		{
			public:

				typedef NoCaseStringHash32 NameIdType;

				//=============================================================================================
				// Public Constructors
				//=============================================================================================
				inline Resource()
					: myResourceNameId()
					, myId()
					, myState(ResourceState::Unloaded)
				{

				}

				explicit inline Resource(NameIdType aResourceNameId, ResourceId<TDerived> anId)
					: myResourceNameId(aResourceNameId)
					, myId(anId)
					, myState(ResourceState::Unloaded)
				{

				}
				
				//=============================================================================================
				// Public Methods
				//=============================================================================================
				inline NameIdType				GetResourceNameId() const;
				inline ResourceId<TDerived>		GetId() const;

				inline ResourceState			GetState() const;
				inline bool						IsLoading() const;
				inline bool						IsLoaded() const;

				inline void						SetFileName(Core::StringView aFileName);
				inline const Core::String&		GetFileName() const;

			protected:

				//=============================================================================================
				// Protected Constructors
				//=============================================================================================
				inline Resource(const Resource<TDerived>& aCopyFrom) = delete;
				inline Resource(Resource<TDerived>&& aMoveFrom) = default;

				//=============================================================================================
				// Protected Methods
				//=============================================================================================
				Resource<TDerived>& operator= (const Resource<TDerived>& aCopyFrom) = delete;
				Resource<TDerived>& operator= (Resource<TDerived>&& aMoveFrom) = default;

				inline void				SetResourceState(ResourceState aResourceState);

			private:

				//=============================================================================================
				// Private Data
				//=============================================================================================
				NameIdType				myResourceNameId;
				ResourceId<TDerived>	myId;

				Core::String			myFileName;

				ResourceState			myState;
		};

		//-----------------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------------
		template <typename TDerived>
		/*inline*/ typename Resource<TDerived>::NameIdType Resource<TDerived>::GetResourceNameId() const
		{
			return myResourceNameId;
		}

		//-----------------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------------
		template <typename TDerived>
		/*inline*/ const Core::String& Resource<TDerived>::GetFileName() const
		{
			return myFileName;
		}

		//-----------------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------------
		template <typename TDerived>
		/*inline*/ void SetFileName(Core::StringView aFileName)
		{
			myFileName = aFileName;
		}

		//-----------------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------------
		template <typename TDerived>
		/*inline*/ ResourceId<TDerived>	Resource<TDerived>::GetId() const
		{
			return myId;
		}

		//-----------------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------------
		template <typename TDerived>
		/*inline*/ ResourceState Resource<TDerived>::GetState() const
		{
			return myState;
		}

		//-----------------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------------
		template <typename TDerived>
		/*inline*/ bool Resource<TDerived>::IsLoading() const
		{
			return GetState() == ResourceState::Loading;
		}

		//-----------------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------------
		template <typename TDerived>
		/*inline*/ bool Resource<TDerived>::IsLoaded() const
		{
			return GetState() == ResourceState::Loaded;
		}

		//-----------------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------------
		template <typename TDerived>
		/*inline*/ void Resource<TDerived>::SetResourceState(ResourceState aResourceState)
		{
			myState = aResourceState;
		}
	}
}