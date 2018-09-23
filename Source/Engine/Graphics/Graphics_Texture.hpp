#pragma once

#include "Graphics_API.hpp"
#include "Core_BasicTypes.hpp"
#include "Core_StringHash.hpp"
#include "Core_SharedPtr.hpp"
#include "Core_Resource.hpp"
#include "Core_ResourceRepository.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		class Texture;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		typedef Core::ResourceHandle<Texture>		TextureHandle;
		typedef Core::ResourceId<Texture>			TextureId;

		//-----------------------------------------------------------------------------------------
		// Name	:	Texture
		// Desc	:	Represents a texture
		//-----------------------------------------------------------------------------------------
		class ALBA_GRAPHICS_API Texture final : public Core::Resource<Texture>
		{
			typedef Core::Resource<Texture> Super;

			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static TextureHandle Get(Core::StringView aFileName);
				static TextureHandle Create(Core::StringView aFileName);
				static TextureHandle Get(Core::Resource<Texture>::NameIdType aResourceNameId);
			
				//=================================================================================
				// Public Constructors
				//=================================================================================
				Texture() = default;

				Texture(const Core::NoCaseStringHash32 aResourceNameId, TextureId anId);
				Texture(const Texture& aCopyFrom) = delete;
				Texture(Texture&& aMoveFrom) = default;

				//=================================================================================
				// Public Methods
				//=================================================================================
				Texture& operator= (const Texture& aCopyFrom) = delete;
				Texture& operator= (Texture&& aMoveFrom) = default;

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
		};
	}
}