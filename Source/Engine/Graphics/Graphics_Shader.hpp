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
		class Shader;
		class ShaderRepository;

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

			private:

				// Ensures that MakeShared can call our constructor, but only from Create
				struct DisableExternalConstruction {};

			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================
				ShaderHandle Get(const Core::StringView& aFileName);

				//=================================================================================
				// Public Constructors/Destructors
				//=================================================================================
				Shader(Core::Resource<Shader>::NameIdType aResourceNameId, ShaderId aShaderId, DisableExternalConstruction&&);
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