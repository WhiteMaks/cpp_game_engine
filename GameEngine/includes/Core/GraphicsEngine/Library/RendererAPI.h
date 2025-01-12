#pragma once

#include "Core/Core.h"

#include "Math/Vector4.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API RendererAPI
	{
	public:
		RendererAPI() noexcept;

	public:
		virtual void Init() noexcept;
		virtual void Destroy() noexcept;

		virtual void SetViewport(const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height) noexcept;
		virtual void ClearColorBuffer() noexcept;
		virtual void ClearDepthBuffer() noexcept;
		virtual void SetClearColor(const Math::Vector4& color) noexcept;
		virtual void DrawTriangles(unsigned int indexCount) noexcept;
	};

}