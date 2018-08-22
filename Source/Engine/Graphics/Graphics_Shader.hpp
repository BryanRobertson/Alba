#pragma once

#include "Graphics_API.hpp"
#include "Core_BasicTypes.hpp"
#include "Core_StringHash.hpp"
#include "Core_Resource.hpp"
#include "Core_ResourceRepository.hpp"

namespace Alba
{
	namespace Graphics
	{
		using namespace Alba::BasicTypes;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		enum class ShaderType : uint8 
		{
			Vertex,
			Pixel,
			Geometry
		};

		class Shader;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		class ALBA_GRAPHICS_API ShaderRepository final : public Core::ResourceRepository<ShaderRepository, Shader>
		{
			typedef Core::ResourceRepository<ShaderRepository, Shader> Super;

			public:

				//=================================================================================
				// Public Constructors
				//=================================================================================
				ShaderRepository();

				//=================================================================================
				// Public Methods
				//=================================================================================
		};

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		typedef Core::ResourceHandle<Shader, ShaderRepository>	ShaderHandle;
		typedef Core::ResourceId<Shader>						ShaderId;

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
				static ShaderHandle Get(Core::StringView aFileName);
				static ShaderHandle Get(NameId aResourceNameId);

				static ShaderHandle CreateFromFile(Core::StringView aFileName);
				static ShaderHandle CreateFromString(NameId aNameId, Core::StringView aShaderSource);

				//=================================================================================
				// Public Constructors/Destructors
				//=================================================================================
				Shader() = default;

				Shader(Core::Resource<Shader>::NameIdType aResourceNameId, ShaderId aShaderId);
				Shader(const Shader& aCopyFrom) = delete;
				Shader(Shader&& aMoveFrom) = default;

				//=================================================================================
				// Public Methods
				//=================================================================================
				Shader& operator=(const Shader& aCopyFrom) = delete;
				Shader& operator=(Shader&& aMoveFrom) = default;

			private:			

				//=================================================================================
				// Private Static Data
				//=================================================================================
				static ShaderRepository		ourShaderRepository;

				//=================================================================================
				// Private Data
				//=================================================================================
				ShaderType					myShaderType;
		};
	}
}