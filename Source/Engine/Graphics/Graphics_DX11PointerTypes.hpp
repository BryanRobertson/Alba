#pragma once

#include "Core_UniquePtr.hpp"
#include <d3d11.h>
#include <wrl/client.h>

//-------------------------------------------------------------------------------------------------
// UniquePtr typedefs for DirectX resources
//-------------------------------------------------------------------------------------------------
namespace Alba
{
	namespace Graphics
	{
		template <typename TDataType>
		using ComPtr = ::Microsoft::WRL::ComPtr<TDataType>;

		typedef ComPtr<IDXGISwapChain>				DXGISwapChainPtr;
		typedef ComPtr<ID3D11Device>				D3D11DevicePtr;
		typedef ComPtr<ID3D11DeviceContext>			D3D11DeviceContextPtr;
		typedef ComPtr<IDXGIAdapter>				DXGIAdapterPtr;
		typedef ComPtr<IDXGIFactory>				DXGIFactoryPtr;

		typedef ComPtr<ID3D11Texture2D>				D3D11Texture2DPtr;
		typedef ComPtr<ID3D11RenderTargetView>		D3D11RenderTargetViewPtr;

		typedef ComPtr<ID3D11DepthStencilView>		D3D11DepthStencilViewPtr;

		typedef ComPtr<ID3D11PixelShader>			D3D11PixelShaderPtr;
		typedef ComPtr<ID3D11VertexShader>			D3D11VertexShaderPtr;
		typedef ComPtr<ID3D11GeometryShader>		D3D11GeometryShaderPtr;
		typedef ComPtr<ID3D11HullShader>			D3D11HullShaderPtr;
		typedef ComPtr<ID3D11DomainShader>			D3D11DomainShaderPtr;
		typedef ComPtr<ID3D11ComputeShader>			D3D11ComputeShaderPtr;
	}
}