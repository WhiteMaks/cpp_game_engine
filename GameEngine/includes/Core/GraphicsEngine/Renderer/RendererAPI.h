#pragma once

#include "VertexArrayBuffer.h"
#include "Tools/Math/Vector4.h"

namespace GraphicsEngine
{

	class RendererAPI
	{
	public:
		virtual void Init() noexcept;
		virtual void Destroy() noexcept;

		virtual void ClearColorBuffer() noexcept;
		virtual void SetClearColor(const Math::Vector4& color) noexcept;
		virtual void DrawTriangles(std::shared_ptr<VertexArrayBuffer> buffer) noexcept;
	};

}