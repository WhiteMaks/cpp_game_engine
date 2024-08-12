#pragma once

#include "Core/GraphicsEngine/Renderer/Buffers/VertexArrayBuffer.h"
#include "Tools/Math/Vector4.h"

namespace GraphicsEngine
{

	class RendererAPI
	{
	public:
		virtual void Init() noexcept;
		virtual void Destroy() noexcept;

		virtual void SetViewport(const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height) noexcept;
		virtual void ClearColorBuffer() noexcept;
		virtual void ClearDepthBuffer() noexcept;
		virtual void SetClearColor(const Math::Vector4& color) noexcept;
		virtual void DrawTriangles(std::shared_ptr<VertexArrayBuffer> buffer) noexcept;
	};

}