#include <comdef.h>
#include "DirectX12Context.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")

namespace GraphicsEngine
{
	DirectX12Context::DirectX12Context(HWND window) noexcept
		: window(window)
	{
	}

	void DirectX12Context::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization directX 12 has started");

		GRAPHICS_ENGINE_DEBUG("Initialization DXGI factory has started");
		HRESULT result = CreateDXGIFactory2(
			0,
			IID_PPV_ARGS(&factory)
		);
		
		if (!SUCCEEDED(result))
		{
			GRAPHICS_ENGINE_CRITICAL("DXGI factory not initialized!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}
		GRAPHICS_ENGINE_DEBUG("Initialization DXGI factory completed");

		GRAPHICS_ENGINE_DEBUG("Initialization DXGI adapter has started");
		result = factory->EnumAdapterByGpuPreference(
			0,
			DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
			IID_PPV_ARGS(&adapter)
		);
		
		if (!SUCCEEDED(result))
		{
			GRAPHICS_ENGINE_CRITICAL("DXGI adapter not initialized!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}

		DXGI_ADAPTER_DESC3 adapterDesc;
		adapter->GetDesc3(&adapterDesc);
		_bstr_t wcharDescription(adapterDesc.Description);
		const char* charDescription = wcharDescription;
		GRAPHICS_ENGINE_TRACE("Selected GPU adapter [{0}]", charDescription);
		GRAPHICS_ENGINE_DEBUG("Initialization DXGI adapter completed");

		GRAPHICS_ENGINE_DEBUG("Initialization d3d12 device has started");
		result = D3D12CreateDevice(
			adapter.Get(),
			D3D_FEATURE_LEVEL_12_2,
			IID_PPV_ARGS(&device)
		);

		if (!SUCCEEDED(result))
		{
			GRAPHICS_ENGINE_CRITICAL("Device not initialized!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}

		GRAPHICS_ENGINE_DEBUG("Initialization d3d12 device completed");

		GRAPHICS_ENGINE_INFO("Initialization directX 12 completed");
	}

	void DirectX12Context::SwapBuffers() noexcept
	{
	}

	void DirectX12Context::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction directX 12 context has started");
		
		device.Reset();
		GRAPHICS_ENGINE_TRACE("Device removed from memory");

		adapter.Reset();
		GRAPHICS_ENGINE_TRACE("DXGI adapter removed from memory");

		factory.Reset();
		GRAPHICS_ENGINE_TRACE("DXGI factory removed from memory");

		GRAPHICS_ENGINE_INFO("Destruction directX 12 completed");
	}

}