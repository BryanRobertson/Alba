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
		/*static*/ TextureHandle Texture::Get(Core::StringView aFileName)
		{
			const Core::NoCaseStringHash32 resourceNameId(aFileName);

			TextureHandle handle = ourTextureRepository.GetResource(resourceNameId);
			if (!handle.IsValid())
			{
				handle = ourTextureRepository.CreateResource(resourceNameId);
				ALBA_ASSERT(handle.IsValid(), "Failed to create resource \"%s\"", aFileName.data());

				handle.LockMutable()->SetFileName(aFileName);
				handle.Unlock();
			}

			return handle;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ TextureHandle Texture::Create(Core::StringView aFileName)
		{
			const Core::NoCaseStringHash32 resourceNameId(aFileName);

			TextureHandle handle = ourTextureRepository.CreateResource(resourceNameId);
			ALBA_ASSERT(handle.IsValid(), "Failed to create resource \"%s\"", aFileName.data());

			handle.LockMutable()->SetFileName(aFileName);
			handle.Unlock();

			return handle;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ TextureHandle Texture::Get(Core::Resource<Texture>::NameIdType aResourceNameId)
		{
			const TextureHandle handle = ourTextureRepository.GetResource(aResourceNameId);
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