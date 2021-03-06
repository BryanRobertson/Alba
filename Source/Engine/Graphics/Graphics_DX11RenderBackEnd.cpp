#include "Graphics_Precompile.hpp"
#include "Graphics_DX11RenderBackEnd.hpp"
#include "Graphics_InitParams.hpp"
#include "Graphics_ImGuiModule.hpp"
#include "Core_ArrayView.hpp"

#include <d3d11.h>
#include <dxgi1_3.h>
#include <wrl/client.h>

#include "Graphics_ImGui.hpp"

#if defined(ALBA_IMGUI_ENABLED)
#	include <examples/imgui_impl_dx11.h>
#	include <examples/imgui_impl_dx11.cpp>
#endif

namespace Alba
{
	namespace Graphics
	{
		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		DX11RenderBackEnd::DX11RenderBackEnd()
			: myFeatureLevel()
			, myIsImGuiInitialised(false)
		{

		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		DX11RenderBackEnd::~DX11RenderBackEnd()
		{
			ShutDown();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 DX11RenderBackEnd::Init(const InitParams& anInitParams)
		{
			//-------------------------------------------------------------------------------------
			// Create Device
			//-------------------------------------------------------------------------------------
			{
				const uint32 result = CreateDevice(anInitParams);
				if (result != 0)
				{
					return result;
				}
			}

			//-------------------------------------------------------------------------------------
			// Create Swap chain
			//-------------------------------------------------------------------------------------
			{
				const uint32 result = CreateSwapChain(anInitParams);
				if (result != 0)
				{
					return result;
				}
			}

			//-------------------------------------------------------------------------------------
			// Create main render target
			//-------------------------------------------------------------------------------------
			{
				const uint32 result = CreateMainRenderTarget(anInitParams);
				if (result != 0)
				{
					return result;
				}
			}

			//-------------------------------------------------------------------------------------
			// Create depth stencil view
			//-------------------------------------------------------------------------------------
			{
				const uint32 result = CreateDepthStencilView(anInitParams);
				if (result != 0)
				{
					return result;
				}
			}

			//-------------------------------------------------------------------------------------
			// Create viewport
			//-------------------------------------------------------------------------------------
			{
				const uint32 result = CreateViewport(anInitParams);
				if (result != 0)
				{
					return result;
				}
			}

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 DX11RenderBackEnd::CreateDevice(const InitParams& /*anInitParams*/)
		{
			D3D_FEATURE_LEVEL levels[] =
			{
				D3D_FEATURE_LEVEL_11_1,
				D3D_FEATURE_LEVEL_11_0
			};

			// This flag adds support for surfaces with a color-channel ordering different
			// from the API default. It is required for compatibility with Direct2D.
			UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(ALBA_DEBUG_BUILD) || defined(ALBA_DEBUG_RENDERING_ENABLED)
			deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

			HRESULT result = D3D11CreateDevice
			(
				nullptr,                    // Specify nullptr to use the default adapter.
				D3D_DRIVER_TYPE_HARDWARE,   // Create a device using the hardware graphics driver.
				0,                          // Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
				deviceFlags,                // Set debug and Direct2D compatibility flags.
				levels,                     // List of feature levels this app can support.
				ARRAYSIZE(levels),          // Size of the list above.
				D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Windows Store apps.
				myDevice.GetAddressOf(),	// Returns the Direct3D device created.
				&myFeatureLevel,            // Returns feature level of device created.
				myDeviceContext.GetAddressOf() // Returns the device immediate context.
			);

			if (FAILED(result))
			{
				return GetLastError();
			}

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 DX11RenderBackEnd::CreateSwapChain(const InitParams& anInitParams)
		{
			DXGI_SWAP_CHAIN_DESC swapChainDesc;

			ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
			swapChainDesc.Windowed = TRUE;							// Sets the initial state of full-screen mode.
			swapChainDesc.BufferCount = 2;
			swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.SampleDesc.Count = 1;							//Multisampling setting
			swapChainDesc.SampleDesc.Quality = 0;							//Vendor-specific flag
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
			swapChainDesc.OutputWindow = anInitParams.myPlatformData.Get<HWND>();

			// Create the DXGI device object to use in other factories, such as Direct2D.
			Microsoft::WRL::ComPtr<IDXGIDevice3> dxgiDevice;
			myDevice.As(&dxgiDevice);

			HRESULT result = dxgiDevice->GetAdapter(myAdapter.GetAddressOf());

			if (FAILED(result))
			{
				return result;
			}

			myAdapter->GetParent(IID_PPV_ARGS(myFactory.GetAddressOf()));
			result = myFactory->CreateSwapChain
			(
				myDevice.Get(),
				&swapChainDesc,
				&mySwapChain
			);

			if (FAILED(result))
			{
				return result;
			}

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 DX11RenderBackEnd::CreateMainRenderTarget(const InitParams& /*anInitParams*/)
		{
			HRESULT result = mySwapChain->GetBuffer
			(
				0,
				__uuidof(ID3D11Texture2D),
				(void**)myBackBuffer.GetAddressOf()
			);

			if (FAILED(result))
			{
				return result;
			}

			result = myDevice->CreateRenderTargetView
			(
				myBackBuffer.Get(),
				nullptr,
				myRenderTarget.GetAddressOf()
			);

			if (FAILED(result))
			{
				return result;
			}

			myBackBuffer->GetDesc(&myBackBufferDesc);

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 DX11RenderBackEnd::CreateDepthStencilView(const InitParams& /*anInitParams*/)
		{
			CD3D11_TEXTURE2D_DESC depthStencilDesc
			(
				DXGI_FORMAT_D24_UNORM_S8_UINT,
				static_cast<UINT> (myBackBufferDesc.Width),
				static_cast<UINT> (myBackBufferDesc.Height),
				1, // This depth stencil view has only one texture.
				1, // Use a single mipmap level.
				D3D11_BIND_DEPTH_STENCIL
			);

			myDevice->CreateTexture2D
			(
				&depthStencilDesc,
				nullptr,
				myDepthStencil.GetAddressOf()
			);

			CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);

			myDevice->CreateDepthStencilView
			(
				myDepthStencil.Get(),
				&depthStencilViewDesc,
				myDepthStencilView.GetAddressOf()
			);

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 DX11RenderBackEnd::CreateViewport(const InitParams& /*anInitParams*/)
		{
			ZeroMemory(&myViewport, sizeof(D3D11_VIEWPORT));

			myViewport.Height = (float)myBackBufferDesc.Height;
			myViewport.Width = (float)myBackBufferDesc.Width;
			myViewport.MinDepth = 0;
			myViewport.MaxDepth = 1;

			myDeviceContext->RSSetViewports
			(
				1,
				&myViewport
			);

			return 0;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void DX11RenderBackEnd::ClearBuffer(const Math::Vector4f& aColour)
		{
			const float colour[] = { aColour[0], aColour[1], aColour[2], aColour[3] };

			myDeviceContext->ClearRenderTargetView
			(
				myRenderTarget.Get(),
				colour
			);

			myDeviceContext->ClearDepthStencilView
			(
				myDepthStencilView.Get(),
				D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
				0.0f,
				0
			);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void DX11RenderBackEnd::Present()
		{
			mySwapChain->Present(0, 0);
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void DX11RenderBackEnd::ShutDown()
		{
			ImGuiShutDown();

			myRenderTarget.Reset();
			myDepthStencilView.Reset();
			myBackBuffer.Reset();
			myFactory.Reset();
			myAdapter.Reset();
			myDeviceContext.Reset();
			mySwapChain.Reset();
			myDevice.Reset();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void DX11RenderBackEnd::BeginFrame()
		{
#			if defined(ALBA_IMGUI_ENABLED)
			{
				if (ImGuiModule::IsLoaded())
				{
					ImGui_ImplDX11_NewFrame();
				}
			}
#			endif

			ID3D11RenderTargetView* renderTarget = myRenderTarget.Get();
			myDeviceContext->OMSetRenderTargets(1, &renderTarget, myDepthStencilView.Get());
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void DX11RenderBackEnd::EndFrame()
		{
#			if defined(ALBA_IMGUI_ENABLED)
			{
				if (ImGuiModule::IsLoaded())
				{
					ImGui::Render();
					ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
				}
			}
#			endif

			Present();
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		bool DX11RenderBackEnd::ImGuiInit()
		{
#			if defined(ALBA_IMGUI_ENABLED)
			{
				if (!ImGui_ImplDX11_Init(myDevice.Get(), myDeviceContext.Get()))
				{
					return false;
				}

				if (!ImGui_ImplDX11_CreateDeviceObjects())
				{
					return false;
				}

				myIsImGuiInitialised = true;
			}
#			endif
			return true;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		void DX11RenderBackEnd::ImGuiShutDown()
		{
#			if defined(ALBA_IMGUI_ENABLED)
			{
				ImGuiModule& imGuiModule = ImGuiModule::Get();
				if (imGuiModule.IsLoaded() && myIsImGuiInitialised)
				{
					ImGui_ImplDX11_Shutdown();
					myIsImGuiInitialised = false;
				}
			}
#			endif
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 DX11RenderBackEnd::CreateShaderFromString(Shader& /*aShader*/, Core::StringView /*aString*/)
		{
			return 1;
		}

		//-----------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------
		uint32 DX11RenderBackEnd::CreateTexture(Texture& /*aTexture*/, Core::ArrayView<std::byte> /*aData*/)
		{
			return 1;
		}
	}
}