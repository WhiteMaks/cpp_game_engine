#include "DirectX12Context.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")

namespace GraphicsEngine
{
	DirectX12Context::DirectX12Context(HWND window) noexcept
		: window(window), currentBuffer(0), rtvHeapIncrement(0), fenceEvent(nullptr), fenceValue()
	{
	}

	void DirectX12Context::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization directX 12 has started");
		InitDXGIFactory();
		InitDXGIAdapter();
		InitD3D12Device();
		InitD3D12CommandQueue();
		InitD3D12Fence();
		InitD3D12CommandAllocator();
		InitD3D12CommandList();
		InitD3D12RTVDescriptorHeap();
		InitDXGISwapChain();
		InitD3D12RenderTargetView();
		GRAPHICS_ENGINE_INFO("Initialization directX 12 completed");
	}

	void DirectX12Context::SwapBuffers() noexcept
	{
		HRESULT result;

		currentBuffer = swapChain->GetCurrentBackBufferIndex();

		if (fence[currentBuffer]->GetCompletedValue() < fenceValue[currentBuffer])
		{
			result = fence[currentBuffer]->SetEventOnCompletion(fenceValue[currentBuffer], fenceEvent);
			if (!SUCCEEDED(result))
			{
				GRAPHICS_ENGINE_CRITICAL("Critical fence error!");
				exit(GameEngine::GRAPHICS_CONTEXT_SWAP_BUFFER_ERROR);
			}

			WaitForSingleObject(fenceEvent, INFINITE);
		}

		fenceValue[currentBuffer]++;

		result = commandAllocator[currentBuffer]->Reset();
		if (!SUCCEEDED(result))
		{
			GRAPHICS_ENGINE_CRITICAL("Critical command allocator reset error!");
			exit(GameEngine::GRAPHICS_CONTEXT_SWAP_BUFFER_ERROR);
		}

		result = commandList->Reset(commandAllocator[currentBuffer].Get(), NULL);
		if (!SUCCEEDED(result))
		{
			GRAPHICS_ENGINE_CRITICAL("Critical command list reset error!");
			exit(GameEngine::GRAPHICS_CONTEXT_SWAP_BUFFER_ERROR);
		}

		D3D12_RESOURCE_BARRIER renderBarrier = {};
		renderBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		renderBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		renderBarrier.Transition.pResource = renderTargetView[currentBuffer].Get();
		renderBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		renderBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		renderBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

		commandList->ResourceBarrier(
			1, 
			&renderBarrier
		);

		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += (size_t) currentBuffer * rtvHeapIncrement;

		commandList->OMSetRenderTargets(
			1,
			&rtvHandle,
			FALSE,
			nullptr
		);

		const float clearColor[] = {0.0f, 0.0f, 1.0f, 1.0f};
		commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

		D3D12_RESOURCE_BARRIER presentBarrier = {};
		presentBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		presentBarrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		presentBarrier.Transition.pResource = renderTargetView[currentBuffer].Get();
		presentBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		presentBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		presentBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

		commandList->ResourceBarrier(
			1,
			&presentBarrier
		);

		result = commandList->Close();
		if (!SUCCEEDED(result))
		{
			GRAPHICS_ENGINE_CRITICAL("Critical command list close error!");
			exit(GameEngine::GRAPHICS_CONTEXT_SWAP_BUFFER_ERROR);
		}

		ID3D12CommandList* ppCommandLists[] = { commandList.Get()};

		commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

		result = commandQueue->Signal(fence[currentBuffer].Get(), fenceValue[currentBuffer]);
		if (!SUCCEEDED(result))
		{
			GRAPHICS_ENGINE_CRITICAL("Critical command queue signal error!");
			exit(GameEngine::GRAPHICS_CONTEXT_SWAP_BUFFER_ERROR);
		}

		result = swapChain->Present(0, 0);
		if (!SUCCEEDED(result))
		{
			GRAPHICS_ENGINE_CRITICAL("Critical swap chain present error!");
			exit(GameEngine::GRAPHICS_CONTEXT_SWAP_BUFFER_ERROR);
		}
	}

	void DirectX12Context::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction directX 12 context has started");

		CloseHandle(fenceEvent);

		swapChain.Reset();
		GRAPHICS_ENGINE_TRACE("DXGI swap chain removed from memory");

		for (int i = 0; i < bufferCount; i++)
		{
			renderTargetView[i].Reset();
		}
		GRAPHICS_ENGINE_TRACE("Render target view removed from memory");

		rtvDescriptorHeap.Reset();
		GRAPHICS_ENGINE_TRACE("Descriptor heap removed from memory");

		commandList.Reset();
		GRAPHICS_ENGINE_TRACE("Command list removed from memory");

		for (int i = 0; i < bufferCount; i++)
		{
			commandAllocator[i].Reset();
		}
		GRAPHICS_ENGINE_TRACE("Command allocator removed from memory");

		commandQueue.Reset();
		GRAPHICS_ENGINE_TRACE("Command queue removed from memory");

		for (int i = 0; i < bufferCount; i++)
		{
			fence[i].Reset();
		}
		GRAPHICS_ENGINE_TRACE("Fence removed from memory");

		device.Reset();
		GRAPHICS_ENGINE_TRACE("Device removed from memory");

		adapter.Reset();
		GRAPHICS_ENGINE_TRACE("DXGI adapter removed from memory");

		factory.Reset();
		GRAPHICS_ENGINE_TRACE("DXGI factory removed from memory");

		GRAPHICS_ENGINE_INFO("Destruction directX 12 completed");
	}

	void DirectX12Context::InitDXGIFactory() noexcept
	{
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
	}

	void DirectX12Context::InitDXGIAdapter() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Initialization DXGI adapter has started");
		HRESULT result = factory->EnumAdapterByGpuPreference(
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
	}

	void DirectX12Context::InitD3D12Device() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Initialization d3d12 device has started");
		HRESULT result = D3D12CreateDevice(
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
	}

	void DirectX12Context::InitD3D12CommandQueue() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Initialization d3d12 command queue has started");
		D3D12_COMMAND_QUEUE_DESC commandQueueDesc = {};
		commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_HIGH;
		commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		commandQueueDesc.NodeMask = 0;

		HRESULT result = device->CreateCommandQueue(
			&commandQueueDesc,
			IID_PPV_ARGS(&commandQueue)
		);

		if (!SUCCEEDED(result))
		{
			GRAPHICS_ENGINE_CRITICAL("Command queue not initialized!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}
		GRAPHICS_ENGINE_DEBUG("Initialization d3d12 command queue completed");
	}

	void DirectX12Context::InitD3D12Fence() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Initialization d3d12 fence has started");
		for (int i = 0; i < bufferCount; i++)
		{
			HRESULT result = device->CreateFence(
				0,
				D3D12_FENCE_FLAG_NONE,
				IID_PPV_ARGS(&fence[i])
			);

			if (!SUCCEEDED(result))
			{
				GRAPHICS_ENGINE_CRITICAL("Fence not initialized!");
				exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
			}
		}

		fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		if (fenceEvent == nullptr)
		{
			GRAPHICS_ENGINE_CRITICAL("Fence event not initialized!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}
		GRAPHICS_ENGINE_DEBUG("Initialization d3d12 fence completed");
	}

	void DirectX12Context::InitD3D12CommandAllocator() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Initialization d3d12 command allocator has started");
		for (int i = 0; i < bufferCount; i++)
		{
			HRESULT result = device->CreateCommandAllocator(
				D3D12_COMMAND_LIST_TYPE_DIRECT,
				IID_PPV_ARGS(&commandAllocator[i])
			);

			if (!SUCCEEDED(result))
			{
				GRAPHICS_ENGINE_CRITICAL("Command allocator not initialized!");
				exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
			}
		}
		GRAPHICS_ENGINE_DEBUG("Initialization d3d12 command allocator completed");
	}

	void DirectX12Context::InitD3D12CommandList() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Initialization d3d12 command list has started");
		HRESULT result = device->CreateCommandList(
			0,
			D3D12_COMMAND_LIST_TYPE_DIRECT,
			commandAllocator[0].Get(),
			nullptr,
			IID_PPV_ARGS(&commandList)
		);

		if (!SUCCEEDED(result))
		{
			GRAPHICS_ENGINE_CRITICAL("Command list not initialized!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}

		commandList->Close();
		GRAPHICS_ENGINE_DEBUG("Initialization d3d12 command list completed");
	}

	void DirectX12Context::InitDXGISwapChain() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Initialization DXGI swap chain has started");

		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = 0;
		swapChainDesc.Height = 0;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.Stereo = FALSE;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = bufferCount;
		swapChainDesc.Scaling = DXGI_SCALING_NONE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING | DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		Microsoft::WRL::ComPtr<IDXGISwapChain1> tempSwapChain;
		HRESULT result = factory->CreateSwapChainForHwnd(
			commandQueue.Get(),
			window,
			&swapChainDesc,
			nullptr,
			nullptr,
			&tempSwapChain
		);

		if (!SUCCEEDED(result))
		{
			GRAPHICS_ENGINE_CRITICAL("DXGI swap chain not initialized!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}

		swapChain = static_cast<IDXGISwapChain4*>(tempSwapChain.Get());
		currentBuffer = swapChain->GetCurrentBackBufferIndex();
		GRAPHICS_ENGINE_DEBUG("Initialization DXGI swap chain completed");
	}

	void DirectX12Context::InitD3D12RenderTargetView() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Initialization d3d12 render target view has started");
		for (int i = 0; i < bufferCount; i++)
		{
			HRESULT result = swapChain->GetBuffer(
				i,
				IID_PPV_ARGS(&renderTargetView[i])
			);

			if (!SUCCEEDED(result))
			{
				GRAPHICS_ENGINE_CRITICAL("DXGI render target view not initialized!");
				exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
			}

			//D3D12_RENDER_TARGET_VIEW_DESC renderTargetViewDesc = {};
			//renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			//renderTargetViewDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

			D3D12_CPU_DESCRIPTOR_HANDLE cpuHandler = rtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
			cpuHandler.ptr += (size_t) rtvHeapIncrement * i;

			device->CreateRenderTargetView(
				renderTargetView[i].Get(),
				nullptr,
				//renderTargetViewDesc,
				cpuHandler
			);
		}
		GRAPHICS_ENGINE_DEBUG("Initialization d3d12 render target view completed");
	}

	void DirectX12Context::InitD3D12RTVDescriptorHeap() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Initialization d3d12 RTV descriptor heap has started");
		D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = {};
		descriptorHeapDesc.NumDescriptors = bufferCount;
		descriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		descriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		descriptorHeapDesc.NodeMask = 0;

		HRESULT result = device->CreateDescriptorHeap(
			&descriptorHeapDesc,
			IID_PPV_ARGS(&rtvDescriptorHeap)
		);

		if (!SUCCEEDED(result))
		{
			GRAPHICS_ENGINE_CRITICAL("RTV descriptor heap not initialized!");
			exit(GameEngine::GRAPHICS_CONTEXT_INITIALIZAATION_FAILED);
		}

		rtvHeapIncrement = device->GetDescriptorHandleIncrementSize(descriptorHeapDesc.Type);
		GRAPHICS_ENGINE_DEBUG("Initialization d3d12 RTV descriptor heap completed");
	}

}