#pragma once

#include "Graphics_API.hpp"
#include "Core_BasicTypes.hpp"
#include "Core_StringHash.hpp"
#include "Core_Resource.hpp"
#include "Core_SharedPtr.hpp"

namespace Alba
{
	namespace Graphics
	{
		using namespace Alba::BasicTypes;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		class Shader;
		
		/*
		struct ALBA_GRAPHICS_API ShaderDeleter final
		{
			void operator()(Shader* aShader) const noexcept;
		};
		*/

		typedef Core::SharedPtr<Shader> ShaderPtr;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		enum class ShaderType : uint8 
		{
			Vertex,
			Pixel,
			Geometry
		};

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
				ShaderPtr Create(const Core::StringView& aFileName);

				//=================================================================================
				// Public Constructors/Destructors
				//=================================================================================
				Shader(Core::Resource<Shader>::NameIdType aResourceNameId, DisableExternalConstruction);
				Shader(const Shader& aCopyFrom) = delete;
				Shader(Shader&& aMoveFrom) = default;

				//=================================================================================
				// Public Methods
				//=================================================================================
				Shader& operator=(const Shader& aCopyFrom) = delete;
				Shader& operator=(Shader&& aMoveFrom) = default;

			private:			

				//=================================================================================
				// Private Data
				//=================================================================================
				ShaderType					myShaderType;
		};
	}
}