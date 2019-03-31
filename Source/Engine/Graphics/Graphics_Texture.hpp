#pragma once

#include "Graphics_API.hpp"
#include "Core_BasicTypes.hpp"
#include "Core_StringHash.hpp"
#include "Core_SharedPtr.hpp"
#include "Core_Resource.hpp"
#include "Core_ResourceRepository.hpp"
#include "Core_Any.hpp"

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
		//-----------------------------------------------------------------------------------------
		enum class TextureType
		{
			Texture1D,
			Texture2D,
			Texture3D
		};

		//-----------------------------------------------------------------------------------------
		// Name	:	Texture
		// Desc	:	Represents a texture
		//-----------------------------------------------------------------------------------------
		class Texture final : public Core::Resource<Texture>
		{
			typedef Core::Resource<Texture> Super;

			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static TextureHandle Get(TextureType aTextureType, Core::StringView aFileName);
				static TextureHandle Create(TextureType aTextureType, Core::StringView aFileName);
				static TextureHandle Get(Core::NoCaseStringHash32 aResourceNameId);

				static TextureHandle CreateFromFile(Core::StringView aFileName);
			
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

				inline const Core::Any&	GetPlatformData() const;
				inline Core::Any&		GetPlatformDataMutable();

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				bool	LoadFromFile(Core::StringView aFileName);

				//=================================================================================
				// Private Data
				//=================================================================================
				TextureType myTextureType = TextureType::Texture2D;
				Core::Any	myPlatformData;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		inline const Core::Any& Texture::GetPlatformData() const
		{
			return myPlatformData;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		inline Core::Any& Texture::GetPlatformDataMutable()
		{
			return myPlatformData;
		}
	}
}