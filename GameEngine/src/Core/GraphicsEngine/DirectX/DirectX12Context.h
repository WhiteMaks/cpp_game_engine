#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <Windows.h>

#include "Core/GraphicsEngine/Renderer/GraphicsContext.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

namespace GraphicsEngine
{

	class DirectX12Context : public GraphicsContext
	{
	private:
		HWND window;
		Microsoft::WRL::ComPtr<IDXGIFactory6> factory;
		Microsoft::WRL::ComPtr<IDXGIAdapter4> adapter;
		Microsoft::WRL::ComPtr<ID3D12Device10> device;

	public:
		DirectX12Context(HWND window) noexcept;

	public:
		void Init() noexcept override;
		void SwapBuffers() noexcept override;
		void Destroy() noexcept override;
	};

}