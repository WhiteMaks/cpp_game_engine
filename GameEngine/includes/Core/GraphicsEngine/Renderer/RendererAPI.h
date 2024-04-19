#pragma once

#include <glm/glm.hpp>

#include "VertexArrayBuffer.h"

namespace GraphicsEngine
{

	class RendererAPI
	{
	public:
		virtual void Init() noexcept;
		virtual void Destroy() noexcept;

		virtual void ClearColorBuffer() noexcept;
		virtual void SetClearColor(const glm::vec4& color) noexcept;
		virtual void DrawTriangles(std::shared_ptr<VertexArrayBuffer> buffer) noexcept;
	};

}