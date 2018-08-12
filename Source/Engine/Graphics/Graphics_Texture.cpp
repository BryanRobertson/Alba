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
			TextureHandle handle = ourTextureRepository.GetOrCreateResource(aFileName, Core::NoCaseStringHash32(aFileName));
			return handle;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Texture::Texture(const Core::NoCaseStringHash32 aResourceNameId, TextureId anId)
			: Super(aResourceNameId, anId)
		{

		}
	}
}