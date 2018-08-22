#pragma once

#include "Graphics_API.hpp"
#include "Graphics_RenderBackEnd.hpp"
#include "Graphics_DX11PointerTypes.hpp"
#include "Core_Assert.hpp"
#include "Math_Vector.hpp"

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		// Name	:	DX11RenderBackEnd
		// Desc	:	Base class for renderer implementations using a specific graphics API
		//-----------------------------------------------------------------------------------------
		class ALBA_GRAPHICS_API DX11RenderBackEnd : public RenderBackEnd
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
				virtual uint32	Init(const InitParams& anInitParams) override;
				virtual void	ClearBuffer(const Math::Vector4f& aColour) override;
				virtual void	Present() override;
				virtual void	ShutDown() override;

				virtual uint32	CreateVertexShaderFromString(ShaderId aShaderId, Core::StringView aString) override;
				virtual uint32	CreateVertexShaderFromFile(ShaderId aShaderId, Core::StringView aFileName) override;

				virtual uint32	CreatePixelShaderFromString(ShaderId aShaderId, Core::StringView aString) override;
				virtual uint32	CreatePixelShaderFromFile(ShaderId aShaderId, Core::StringView aFileName) override;

			private:

				//=================================================================================
				// Private Methods
				//=================================================================================
				uint32			CreateDevice(const InitParams& anInitParams);
				uint32			CreateSwapChain(const InitParams& anInitParams);
				uint32			CreateMainRenderTarget(const InitParams& anInitParams);
				uint32			CreateDepthStencilView(const InitParams& anInitParams);
				uint32			CreateViewport(const InitParams& anInitParams);

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

				D3D11_VIEWPORT				myViewport;
		};
	}
}