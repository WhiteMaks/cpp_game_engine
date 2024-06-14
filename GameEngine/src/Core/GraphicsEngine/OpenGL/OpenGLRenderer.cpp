#include "OpenGLRenderer.h"

namespace GraphicsEngine
{
	
	void OpenGLRenderer::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization openGL renderer has started");
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		GRAPHICS_ENGINE_INFO("Initialization openGL renderer completed");
	}

	void OpenGLRenderer::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction openGL renderer has started");
		GRAPHICS_ENGINE_INFO("Destruction openGL renderer completed");
	}

	void OpenGLRenderer::ClearColorBuffer() noexcept
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderer::SetClearColor(const Math::Vector4& color) noexcept
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderer::DrawTriangles(std::shared_ptr<VertexArrayBuffer> buffer) noexcept
	{
		glDrawElements(GL_TRIANGLES, buffer->GetIndexStaticBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}