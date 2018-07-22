#include "Graphics_Precompile.hpp"
#include "Graphics_Shader.hpp"

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
		ShaderHandle Shader::Get(const Core::StringView& aFileName)
		{
			return ourShaderRepository.GetResource(Core::NoCaseStringHash32(aFileName));
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Shader::Shader(Core::Resource<Shader>::NameIdType aResourceNameId, ShaderId aShaderId, Shader::DisableExternalConstruction&&)
			: Super(aResourceNameId, aShaderId)
		{

		}
	}
}
