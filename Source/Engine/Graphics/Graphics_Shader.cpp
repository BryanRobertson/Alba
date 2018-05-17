#include "Graphics_Precompile.hpp"
#include "Graphics_Shader.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		ShaderPtr Shader::Create(const Core::StringView& aFileName)
		{
			return Core::MakeShared<Shader>(Super::NameIdType(aFileName), DisableExternalConstruction());
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		Shader::Shader(Core::Resource<Shader>::NameIdType aResourceNameId, Shader::DisableExternalConstruction)
			: Super(aResourceNameId)
		{

		}
	}
}
