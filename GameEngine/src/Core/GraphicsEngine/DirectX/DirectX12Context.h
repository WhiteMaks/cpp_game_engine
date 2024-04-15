#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <Windows.h>
#include <comdef.h>

#include "Core/GraphicsEngine/Renderer/GraphicsContext.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

namespace GraphicsEngine
{

	class DirectX12Context : public GraphicsContext
	{
	private:
		static const UINT bufferCount = 2;

		HWND window;

		Microsoft::WRL::ComPtr<IDXGIFactory7> factory;
		Microsoft::WRL::ComPtr<IDXGIAdapter4> adapter;
		Microsoft::WRL::ComPtr<ID3D12Device10> device;
		Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList7> commandList;
		
		Microsoft::WRL::ComPtr<ID3D12Fence1> fence[bufferCount];
		Microsoft::WRL::ComPtr<ID3D12Resource2> renderTargetView[bufferCount];
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator[bufferCount];

		HANDLE fenceEvent;

		UINT currentBuffer;
		UINT rtvHeapIncrement;

		UINT64 fenceValue[bufferCount];

	public:
		DirectX12Context(HWND window) noexcept;

	public:
		void Init() noexcept override;
		void StartFrame() noexcept override;
		void EndFrame() noexcept override;
		void Destroy() noexcept override;

	private:
		void InitDXGIFactory() noexcept;
		void InitDXGIAdapter() noexcept;
		void InitD3D12Device() noexcept;
		void InitD3D12CommandQueue() noexcept;
		void InitD3D12Fence() noexcept;
		void InitD3D12CommandAllocator() noexcept;
		void InitD3D12CommandList() noexcept;
		void InitDXGISwapChain() noexcept;
		void InitD3D12RenderTargetView() noexcept;
		void InitD3D12RTVDescriptorHeap() noexcept;
	};

}