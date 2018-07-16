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

				//=================================================================================
				// Public Constructors
				//=================================================================================
				ResourceHandle()
					: myResourceId(IdType::InvalidId)
				{

				}
				
				explicit ResourceHandle(IdType anId)
					: myResourceId(anId)
				{

				}

				//=================================================================================
				// Public Methods
				//=================================================================================
				IdType GetId() const
				{
					return myResourceId;
				}

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				IdType				 myResourceId;
		};
	}
}