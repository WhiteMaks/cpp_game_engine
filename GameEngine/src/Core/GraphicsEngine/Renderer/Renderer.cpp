#include "Core/GraphicsEngine/Renderer/Renderer.h"

namespace GraphicsEngine
{
	RendererAPI* Renderer::api = nullptr;

	void Renderer::Init() noexcept
	{
		api = RendererAPIFactory::Create();
		api->Init();
	}

	void Renderer::BeginScene() noexcept
	{
	}

	void Renderer::Submit(std::shared_ptr<VertexArrayBuffer> buffer) noexcept
	{
		buffer->Bind();
		api->DrawTriangles(buffer);
		buffer->Unbind();
	}

	void Renderer::EndScene() noexcept
	{
	}

	void Renderer::Destroy() noexcept
	{
		api->Destroy();
	}

	void Renderer::Clear() noexcept
	{
		api->ClearColorBuffer();
	}

	void Renderer::SetClearColor(const glm::vec4& color) noexcept
	{
		api->SetClearColor(color);
	}

}