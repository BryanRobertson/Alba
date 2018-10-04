#pragma once

#include "Graphics_API.hpp"
#include "Core_BasicTypes.hpp"
#include "Core_StringHash.hpp"
#include "Core_Resource.hpp"
#include "Core_ResourceRepository.hpp"
#include "Core_Any.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		enum class ShaderType : uint8 
		{
			Vertex,
			Pixel,
			Geometry,
			Compute,
			Hull,
			Domain
		};

		class Shader;
		class ShaderRepository;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		typedef Core::ResourceHandle<Shader>	ShaderHandle;
		typedef Core::ResourceId<Shader>		ShaderId;

		//-----------------------------------------------------------------------------------------
		// Name	:	Shader
		// Desc	:	Represents a shader program (vertex shader, pixel shader, geometry shader, etc)
		//-----------------------------------------------------------------------------------------
		class ALBA_GRAPHICS_API Shader final : public Core::Resource<Shader>
		{
			typedef Core::Resource<Shader> Super;

			public:

				typedef Core::Resource<Shader>::NameIdType NameId;

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				static ShaderHandle Get(ShaderType aShaderType, Core::StringView aFileName);
				static ShaderHandle Get(NameId aResourceNameId);

				static ShaderHandle CreateFromFile(ShaderType aShaderType, Core::StringView aFileName);
				static ShaderHandle CreateFromString(ShaderType aShaderType, NameId aNameId, Core::StringView aShaderSourceCode);

				//=================================================================================
				// Public Constructors/Destructors
				//=================================================================================
				Shader() = default;

				Shader(Core::Resource<Shader>::NameIdType aResourceNameId, ShaderId aShaderId);
				Shader(const Shader& aCopyFrom) = delete;
				Shader(Shader&& aMoveFrom) = default;

				~Shader();

				//=================================================================================
				// Public Methods
				//=================================================================================
				Shader& operator=(const Shader& aCopyFrom) = delete;
				Shader& operator=(Shader&& aMoveFrom) = default;

				inline const Core::Any&	GetPlatformData() const;
				inline Core::Any&		GetPlatformDataMutable();

			private:			

				//=================================================================================
				// Private Methods
				//=================================================================================
				void	SetType(ShaderType aShaderType);

				bool	LoadFromFile(Core::StringView aFileName);
				bool	LoadFromString(Core::StringView aShaderSourceCode);

				//=================================================================================
				// Private Data
				//=================================================================================
				ShaderType					myShaderType;
				Core::Any					myPlatformData;
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		inline const Core::Any& Shader::GetPlatformData() const
		{
			return myPlatformData;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		inline Core::Any& Shader::GetPlatformDataMutable()
		{
			return myPlatformData;
		}
	}
}