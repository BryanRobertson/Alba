#include "Graphics_Precompile.hpp"
#include "Graphics_Texture.hpp"

namespace Alba
{
	namespace Graphics
	{
		static constexpr size_t ourMaxTextures = 4096;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ TextureRepository Texture::ourTextureRepository;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TextureRepository::TextureRepository()
			: Super(ourMaxTextures)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		TextureHandle Texture::Get(const Core::StringView& aFileName)
		{
			return ourTextureRepository.GetOrCreateResource(Core::NoCaseStringHash32(aFileName));
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Texture::Texture(const Core::NoCaseStringHash32 aResourceNameId, TextureId anId)
			: Super(aResourceNameId, anId)
		{

		}
	}
}