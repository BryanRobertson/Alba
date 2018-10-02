#pragma once

#include "Graphics_API.hpp"
#include "Graphics_Shader.hpp"
#include "Core_BasicTypes.hpp"
#include "Core_Assert.hpp"
#include "Math_Vector.hpp"

namespace Alba
{
	namespace Graphics
	{
		struct InitParams;
		enum class ShaderType : uint8;

		//-----------------------------------------------------------------------------------------
		// Name	:	RenderBackEnd
		// Desc	:	Base class for renderer implementations using a specific graphics API
		//-----------------------------------------------------------------------------------------
		template <typename TImplementation>
		class RenderBackEnd
		{
			public:

				//=================================================================================
				// Public Constructors / Destructors
				//=================================================================================
				RenderBackEnd() = default;

				//=================================================================================
				// Public Methods
				//=================================================================================
				ALBA_FORCEINLINE uint32 Init(const InitParams& someInitParams)
				{
					return myImplementation.Init(someInitParams);
				}

				ALBA_FORCEINLINE void ShutDown()
				{
					return myImplementation.ShutDown();
				}

				ALBA_FORCEINLINE void BeginFrame()
				{
					return myImplementation.BeginFrame();
				}

				ALBA_FORCEINLINE void ClearBuffer(const Math::Vector4f& aColour)
				{
					return myImplementation.ClearBuffer(aColour);
				}

				ALBA_FORCEINLINE void Present()
				{
					return myImplementation.Present();
				}

				ALBA_FORCEINLINE void EndFrame()
				{
					return myImplementation.EndFrame();
				}

				ALBA_FORCEINLINE bool ImGuiInit()
				{
					return myImplementation.ImGuiInit();
				}

				ALBA_FORCEINLINE void ImGuiShutDown()
				{
					return myImplementation.ImGuiShutDown();
				}

				ALBA_FORCEINLINE uint32 CreateShaderFromString(ShaderId aShaderId, ShaderType aShaderType, Core::StringView aString)
				{
					return myImplementation.CreateShaderFromString(aShaderId, aShaderType, aString);
				}

				ALBA_FORCEINLINE void UnloadShader(ShaderId aShaderId)
				{
					return myImplementation.UnloadShader(aShaderId);
				}

			private:

				//=================================================================================
				// Private Data
				//=================================================================================
				TImplementation myImplementation;
		};
	}
}
