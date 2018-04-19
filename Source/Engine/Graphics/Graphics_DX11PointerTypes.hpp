#pragma once

#include "Core_UniquePtr.hpp"
#include <d3d11.h>

//-------------------------------------------------------------------------------------------------
// UniquePtr typedefs for DirectX resources
//-------------------------------------------------------------------------------------------------
namespace Alba
{
	namespace Graphics
	{
		namespace Internal
		{
			template <typename TStoredType>
			struct COMDeleter
			{
				void operator()(TStoredType* p) const EA_NOEXCEPT
				{
					p->Release();
				}
			};
		}

		template <typename TDataType>
		using COMUniquePtr = Core::UniquePtr<TDataType, Internal::COMDeleter<TDataType> >;

		typedef COMUniquePtr<IDXGISwapChain>		DXGISwapChainPtr;
		typedef COMUniquePtr<ID3D11Device>			D3D11DevicePtr;
		typedef COMUniquePtr<ID3D11DeviceContext>	D3D11DeviceContextPtr;
	}
}