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
	}
}