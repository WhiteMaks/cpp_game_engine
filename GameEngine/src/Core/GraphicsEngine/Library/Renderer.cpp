#include "Core/GraphicsEngine/Library/Renderer.h"

#include "Core/GraphicsEngine/GraphicsEngine.h"

namespace GraphicsEngine
{
	std::shared_ptr<RendererAPI> Renderer::api = nullptr;

	void Renderer::Init() noexcept
	{
		api = GraphicsEngine::GetLibrary()->CreateRenderer();
		api->Init();
	}

	void Renderer::Resize(const unsigned int width, const unsigned int height) noexcept
	{
		api->SetViewport(0, 0, width, height);
	}

	void Renderer::DrawTriangles(std::shared_ptr<VertexArrayBuffer> buffer) noexcept
	{
		DrawTriangles(buffer->GetIndexStaticBuffer()->GetCount());
	}

	void Renderer::DrawTriangles(unsigned int indexCount) noexcept
	{
		api->DrawTriangles(indexCount);
	}

	void Renderer::Destroy() noexcept
	{
		api->Destroy();
	}

	void Renderer::Clear() noexcept
	{
		api->ClearColorBuffer();
		api->ClearDepthBuffer();
	}

	void Renderer::SetClearColor(const Math::Vector4& color) noexcept
	{
		api->SetClearColor(color);
	}

}