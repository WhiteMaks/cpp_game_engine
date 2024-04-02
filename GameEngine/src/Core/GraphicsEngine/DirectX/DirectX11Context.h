#pragma once

#include <d3d11.h>
#include <Windows.h>

#include "Core/GraphicsEngine/Renderer/GraphicsContext.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

namespace GraphicsEngine
{

	class DirectX11Context : public GraphicsContext
	{
	private:
		HWND window;
		ID3D11Device* pDevice;
		IDXGISwapChain* pSwapChain;
		ID3D11DeviceContext* pContext;
		ID3D11RenderTargetView* pRenderTargetView;

	public:
		DirectX11Context(HWND window) noexcept;

	public:
		void Init() noexcept override;
		void SwapBuffers() noexcept override;
		void Destroy() noexcept override;
	};

}