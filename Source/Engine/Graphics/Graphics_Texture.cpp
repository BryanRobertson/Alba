#include "Graphics_Precompile.hpp"
#include "Graphics_Texture.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*
		void TextureDeleter::operator()(Texture* aTexture) const noexcept
		{
			delete aTexture;
		}
		*/

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TexturePtr Texture::Create(const Core::StringView& aFileName)
		{
			return Core::MakeShared<Texture>(Super::NameIdType(aFileName), DisableExternalConstruction());
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Texture::Texture(const Core::NoCaseStringHash32 aResourceNameId, DisableExternalConstruction)
			: Super(aResourceNameId)
		{

		}
	}
}