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
		class ALBA_GRAPHICS_API TextureRepository final : public Core::ResourceRepository<TextureRepository, Texture>
		{
			typedef Core::ResourceRepository<TextureRepository, Texture> Super;

		public:

			//=================================================================================
			// Public Constructors
			//=================================================================================
			TextureRepository();

			//=================================================================================
			// Public Methods
			//=================================================================================
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		typedef Core::ResourceHandle<Texture, TextureRepository>	TextureHandle;
		typedef Core::ResourceId<Texture>							TextureId;

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
				static TextureHandle Get(const Core::StringView& aFileName);
			
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
				// Private Constructors
				//=================================================================================

				//=================================================================================
				// Private Static Data
				//=================================================================================
				static TextureRepository		ourTextureRepository;

				//=================================================================================
				// Private Data
				//=================================================================================
		};
	}
}