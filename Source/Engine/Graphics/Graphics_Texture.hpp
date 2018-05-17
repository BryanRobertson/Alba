#pragma once

#include "Graphics_API.hpp"
#include "Core_BasicTypes.hpp"
#include "Core_StringHash.hpp"
#include "Core_SharedPtr.hpp"
#include "Core_Resource.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		class Texture;

		/*
		struct ALBA_GRAPHICS_API TextureDeleter final
		{
			void operator()(Texture* aTexture) const noexcept;
		};
		*/

		typedef Core::SharedPtr<Texture> TexturePtr;

		//-----------------------------------------------------------------------------------------
		// Name	:	Texture
		// Desc	:	Represents a texture
		//-----------------------------------------------------------------------------------------
		class ALBA_GRAPHICS_API Texture final : public Core::Resource<Texture>
		{
			typedef Core::Resource<Texture> Super;

			private:

				// Ensures that MakeShared can call our constructor, but only from Create
				struct DisableExternalConstruction {};

			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				TexturePtr Create(const Core::StringView& aFileName);
			
				//=================================================================================
				// Public Constructors
				//=================================================================================
				Texture(const Core::NoCaseStringHash32 aResourceNameId, DisableExternalConstruction);
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
				// Private Data
				//=================================================================================
		};
	}
}