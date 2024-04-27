#include "WebGLRenderer.h"

namespace GraphicsEngine
{
	
	void WebGLRenderer::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization webGL renderer has started");
		GRAPHICS_ENGINE_INFO("Initialization webGL renderer completed");
	}

	void WebGLRenderer::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction webGL renderer has started");
		GRAPHICS_ENGINE_INFO("Destruction webGL renderer completed");
	}

	void WebGLRenderer::ClearColorBuffer() noexcept
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void WebGLRenderer::SetClearColor(const Math::Vector4& color) noexcept
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void WebGLRenderer::DrawTriangles(std::shared_ptr<VertexArrayBuffer> buffer) noexcept
	{
		glDrawElements(GL_TRIANGLES, buffer->GetIndexStaticBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}