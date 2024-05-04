#include "Core/GraphicsEngine/Renderer/Renderer.h"

namespace GraphicsEngine
{
	RendererAPI* Renderer::api = nullptr;

	glm::mat4 Renderer::viewProjectionMatrix = glm::mat4(1.0f);

	void Renderer::Init() noexcept
	{
		api = RendererAPIFactory::Create();
		api->Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera) noexcept
	{
		viewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::Submit(std::shared_ptr<ShaderProgram> shaderProgram, std::shared_ptr<VertexArrayBuffer> buffer, glm::mat4 modelMatrix) noexcept
	{
		shaderProgram->Bind();
		shaderProgram->SetUniformMat4("u_ViewProjectionMatrix", viewProjectionMatrix);
		shaderProgram->SetUniformMat4("u_ModelMatrix", modelMatrix);

		buffer->Bind();
		api->DrawTriangles(buffer);
		buffer->Unbind();
		shaderProgram->Unbind();
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

	void Renderer::SetClearColor(const Math::Vector4& color) noexcept
	{
		api->SetClearColor(color);
	}

}