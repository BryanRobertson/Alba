#include "Graphics_Precompile.hpp"
#include "Graphics_Shader.hpp"
#include "Core_Assert.hpp"

namespace Alba
{
	namespace Graphics
	{
		static constexpr size_t ourMaxShaders = 2048;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		ShaderRepository::ShaderRepository()
			: Super(ourMaxShaders)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ ShaderRepository	Shader::ourShaderRepository;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ShaderHandle Shader::Get(Core::StringView aFileName)
		{
			const Core::NoCaseStringHash32 resourceNameId(aFileName);

			ShaderHandle handle = ourShaderRepository.GetResource(resourceNameId);
			if (!handle.IsValid())
			{
				handle = ourShaderRepository.CreateResource(resourceNameId);
				ALBA_ASSERT(handle.IsValid(), "Failed to create resource \"%s\"", aFileName.data());

				handle.LockMutable()->SetFileName(aFileName);
				handle.Unlock();
			}

			return handle;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ ShaderHandle Shader::CreateFromFile(Core::StringView aFileName)
		{
			const Core::NoCaseStringHash32 resourceNameId(aFileName);

			ShaderHandle handle = ourShaderRepository.CreateResource(resourceNameId);
			ALBA_ASSERT(handle.IsValid(), "Failed to create resource \"%s\"", aFileName.data());

			handle.LockMutable()->SetFileName(aFileName);
			handle.Unlock();

			return handle;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ ShaderHandle Shader::CreateFromString(NameId aNameId, Core::StringView aShaderSource)
		{
			ALBA_ASSERT(!ourShaderRepository.HasResource(aNameId), "Attempting to create duplicate shader \"%s\"", aNameId.LogString().c_str());

			ShaderHandle handle = ourShaderRepository.CreateResource(aNameId);
			ALBA_ASSERT(handle.IsValid(), "Failed to create resource \"%s\"", aNameId.LogString().c_str());

			return handle;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		/*static*/ ShaderHandle Shader::Get(Core::Resource<Shader>::NameIdType aResourceNameId)
		{
			const ShaderHandle handle = ourShaderRepository.GetResource(aResourceNameId);
			return handle;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Shader::Shader(Core::Resource<Shader>::NameIdType aResourceNameId, ShaderId aShaderId)
			: Super(aResourceNameId, aShaderId)
		{

		}
	}
}
