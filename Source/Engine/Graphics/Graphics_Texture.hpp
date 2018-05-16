#pragma once

#include "Graphics_API.hpp"
#include "Core_BasicTypes.hpp"
#include "Core_StringHash.hpp"
#include "Core_SharedPtr.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		class Texture;
		struct ALBA_GRAPHICS_API TextureDeleter final
		{
			void operator()(Texture* aTexture) const noexcept;
		};

		typedef Core::SharedPtr<Texture> TexturePtr;

		//-----------------------------------------------------------------------------------------
		// Name	:	Texture
		// Desc	:	Represents a texture
		//-----------------------------------------------------------------------------------------
		class ALBA_GRAPHICS_API Texture final
		{
			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
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