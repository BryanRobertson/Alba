#pragma once

#include "Graphics_API.hpp"
#include "Core_BasicTypes.hpp"
#include "Core_StringHash.hpp"

namespace Alba
{
	namespace Graphics
	{
		using namespace Alba::BasicTypes;

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		class Shader;
		struct ALBA_GRAPHICS_API ShaderDeleter final
		{
			void operator()(Shader* aShader) const noexcept;
		};

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
		class ALBA_GRAPHICS_API Shader final
		{
			public:

				//=================================================================================
				// Public Static Methods
				//=================================================================================

				//=================================================================================
				// Public Constructors/Destructors
				//=================================================================================
				Shader(const Shader& aCopyFrom) = delete;
				Shader(Shader&& aMoveFrom) = default;

				//=================================================================================
				// Public Methods
				//=================================================================================
				Core::NoCaseStringHash32 GetNameId() const;
				
				Shader& operator=(const Shader& aCopyFrom) = delete;
				Shader& operator=(Shader&& aMoveFrom) = default;

			private:

				//=================================================================================
				// Private Constructors
				//================================================================================

				//=================================================================================
				// Private Data
				//=================================================================================
				Core::NoCaseStringHash32	myNameId;
				ShaderType					myShaderType;
		};
	}
}