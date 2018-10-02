#pragma once

#include "Graphics_API.hpp"
#include "Graphics_DX11PointerTypes.hpp"
#include "Graphics_Shader.hpp"
#include "Graphics_Texture.hpp"
#include "Core_Assert.hpp"
#include "Core_VectorMap.hpp"
#include "Math_Vector.hpp"

namespace Alba
{
	namespace Graphics
	{
		struct InitParams;

		//-----------------------------------------------------------------------------------------
		// Name	:	DX11RenderBackEnd
		// Desc	:	Base class for renderer implementations using a specific graphics API
		//-----------------------------------------------------------------------------------------
		class DX11RenderBackEnd final
		{
			public:

				//=================================================================================
				// Public Constructors / Destructors
				//=================================================================================
				DX11RenderBackEnd();
				virtual ~DX11RenderBackEnd();

				//=================================================================================
				// Public Methods
				//=================================================================================
				uint32	Init(const InitParams& anInitParams);
				void	BeginFrame() ;
				void	ClearBuffer(const Math::Vector4f& aColour);
				void	Present();
				void	EndFrame();
				void	ShutDown();

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				bool	ImGuiInit();
				void	ImGuiShutDown();

				//---------------------------------------------------------------------------------
				//---------------------------------------------------------------------------------
				uint32	CreateShaderFromString(ShaderId aShaderId, ShaderType aShaderType, Core::StringView aString);
				void	UnloadShader(ShaderId aShaderId);

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				uint32						CreateDevice(const InitParams& anInitParams);
				uint32						CreateSwapChain(const InitParams& anInitParams);
				uint32						CreateMainRenderTarget(const InitParams& anInitParams);
				uint32						CreateDepthStencilView(const InitParams& anInitParams);
				uint32						CreateViewport(const InitParams& anInitParams);

				//=================================================================================
				// Private Data
				//=================================================================================
				D3D11DevicePtr				myDevice;
				DXGISwapChainPtr			mySwapChain;
				D3D11DeviceContextPtr		myDeviceContext;
				DXGIAdapterPtr				myAdapter;
				DXGIFactoryPtr				myFactory;
				D3D_FEATURE_LEVEL			myFeatureLevel;

				D3D11Texture2DPtr			myBackBuffer;
				D3D11_TEXTURE2D_DESC		myBackBufferDesc;

				D3D11Texture2DPtr			myDepthStencil;
				D3D11DepthStencilViewPtr	myDepthStencilView;

				D3D11RenderTargetViewPtr	myRenderTarget;

				Core::VectorMap<ShaderId, D3D11VertexShaderPtr>		myVertexShaders;
				Core::VectorMap<ShaderId, D3D11PixelShaderPtr>		myPixelShaders;
				Core::VectorMap<ShaderId, D3D11GeometryShaderPtr>	myGeometryShaders;
				Core::VectorMap<ShaderId, D3D11HullShaderPtr>		myHullShaders;
				Core::VectorMap<ShaderId, D3D11DomainShaderPtr>		myDomainShaders;
				Core::VectorMap<ShaderId, D3D11ComputeShaderPtr>	myComputeShaders;

				Core::VectorMap<TextureId, D3D11Texture1DPtr>		my1DTextures;
				Core::VectorMap<TextureId, D3D11Texture2DPtr>		my2DTextures;
				Core::VectorMap<TextureId, D3D11Texture3DPtr>		my3DTextures;

				D3D11_VIEWPORT				myViewport;

				bool						myIsImGuiInitialised;
		};
	}
}