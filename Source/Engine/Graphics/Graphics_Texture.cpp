#include "Graphics_Precompile.hpp"
#include "Graphics_Texture.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void TextureDeleter::operator()(Texture* aTexture) const noexcept
		{
			delete aTexture;
		}
	}
}