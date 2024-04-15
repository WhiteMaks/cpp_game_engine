#include "DirectX11Context.h"

#pragma comment(lib, "d3d11.lib")

namespace GraphicsEngine
{
	DirectX11Context::DirectX11Context(HWND window) noexcept
		: window(window), pDevice(nullptr), pSwapChain(nullptr), pContext(nullptr), pRenderTargetView(nullptr)
	{
	}

	void DirectX11Context::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization directX 11 has started");

		GRAPHICS_ENGINE_DEBUG("Initialization d3d11 device and swap chain has started");
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		
		swapChainDesc.BufferDesc.Width = 0; //resolution width. If equal 0, the value will be automatically substituted from the settings of the window
		swapChainDesc.BufferDesc.Height = 0; //resolution height. If equal 0, the value will be automatically substituted from the settings of the window
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		
		swapChainDesc.BufferCount = 1;

		swapChainDesc.OutputWindow = window;

		swapChainDesc.Windowed = TRUE;

		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		swapChainDesc.Flags = 0;

		HRESULT result = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			0,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&pSwapChain,
			&pDevice,
			nullptr,
			&pContext
		);

		if (!SUCCEEDED(result))
		{
			GRAPHICS_ENGINE_CRITICAL("Device or swap chain not initialized!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}

		GRAPHICS_ENGINE_DEBUG("Initialization d3d11 device and swap chain completed");

		GRAPHICS_ENGINE_DEBUG("Initialization d3d11 render target view has started");
		ID3D11Resource* pBackBuffer = nullptr;
		result = pSwapChain->GetBuffer(
			0,
			__uuidof(ID3D11Resource),
			reinterpret_cast<void**>(&pBackBuffer)
		);

		if (!SUCCEEDED(result))
		{
			GRAPHICS_ENGINE_CRITICAL("Back buffer not initialized!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}

		result = pDevice->CreateRenderTargetView(
			pBackBuffer,
			nullptr,
			&pRenderTargetView
		);

		if (!SUCCEEDED(result))
		{
			GRAPHICS_ENGINE_CRITICAL("Render target view not initialized!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}

		pBackBuffer->Release();
		GRAPHICS_ENGINE_DEBUG("Initialization d3d11 render target view completed");

		GRAPHICS_ENGINE_INFO("Initialization directX 11 completed");
	}

	void DirectX11Context::StartFrame() noexcept
	{
		const float color[] = { 0, 0, 1, 1 };
		pContext->ClearRenderTargetView(
			pRenderTargetView,
			color
		);
	}

	void DirectX11Context::EndFrame() noexcept
	{
		pSwapChain->Present(
			0u, //if equal 0, then no synchronization 
			0u
		);
	}

	void DirectX11Context::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction directX 11 context has started");

		if (pRenderTargetView != nullptr)
		{
			pRenderTargetView->Release();
			GRAPHICS_ENGINE_TRACE("Render target view removed from memory");
		}

		if (pContext != nullptr)
		{
			pContext->Release();
			GRAPHICS_ENGINE_TRACE("Context removed from memory");
		}

		if (pSwapChain != nullptr)
		{
			pSwapChain->Release();
			GRAPHICS_ENGINE_TRACE("Swap chain removed from memory");
		}

		if (pDevice != nullptr)
		{
			pDevice->Release();
			GRAPHICS_ENGINE_TRACE("Device removed from memory");
		}

		GRAPHICS_ENGINE_INFO("Destruction directX 11 completed");
	}

}