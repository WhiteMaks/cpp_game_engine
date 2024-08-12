#include "Core/GraphicsEngine/Renderer/RendererAPI.h"

namespace GraphicsEngine
{

	void RendererAPI::Init() noexcept
	{
	}

	void RendererAPI::Destroy() noexcept
	{
	}

	void RendererAPI::SetViewport(const unsigned int x, const unsigned int y, const unsigned int width, const unsigned int height) noexcept
	{
	}

	void RendererAPI::ClearColorBuffer() noexcept
	{
	}

	void RendererAPI::ClearDepthBuffer() noexcept
	{
	}

	void RendererAPI::SetClearColor(const Math::Vector4& color) noexcept
	{
	}

	void RendererAPI::DrawTriangles(std::shared_ptr<VertexArrayBuffer> buffer) noexcept
	{
	}

}