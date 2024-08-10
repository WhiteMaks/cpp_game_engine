#include "Core/GraphicsEngine/Renderer/Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Core/GraphicsEngine/Renderer/Renderer.h"
#include "Core/GraphicsEngine/Assets/ShaderProgramFactory.h"
#include "Core/GraphicsEngine/Renderer/Buffers/BufferFactory.h"

namespace GraphicsEngine
{
	struct Data
	{
		std::shared_ptr<ShaderProgram> shaderProgram;
		std::shared_ptr<VertexArrayBuffer> vertexArrayBuffer;
	};

	static Data data;

	glm::mat4 Renderer2D::viewProjectionMatrix = glm::mat4(1.0f);

	void Renderer2D::Init() noexcept
	{
		data.shaderProgram = std::shared_ptr<ShaderProgram>(
			ShaderProgramFactory::Create("assets/shaders/flat_color_shader")
		);
		data.shaderProgram->Init();

		data.vertexArrayBuffer = std::shared_ptr<VertexArrayBuffer>(
			BufferFactory::CreateVertexArrayBuffer()
		);
		data.vertexArrayBuffer->Init();

		float vertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		/*
		float vertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		*/

		std::shared_ptr<VertexStaticBuffer> vertexBuffer = std::shared_ptr<VertexStaticBuffer>(
			BufferFactory::CreateVertexStaticBuffer(vertices, sizeof(vertices))
		);

		std::vector<BufferElement> bufferElements = {
			{BufferElementType::FLOAT_3, "a_Position"},
			//{BufferElementType::FLOAT_2, "a_TextureCoordinate"},
		};

		BufferLayout bufferLayout(bufferElements);
		bufferLayout.Init();

		vertexBuffer->SetLayout(bufferLayout);
		vertexBuffer->Init();

		data.vertexArrayBuffer->AddVertexBuffer(vertexBuffer);

		unsigned int indices[6] = {
			0, 1, 2, 2, 3, 0
		};

		std::shared_ptr<IndexStaticBuffer> indexBuffer = std::shared_ptr<IndexStaticBuffer>(
			BufferFactory::CreateIndexStaticBuffer(indices, sizeof(indices) / sizeof(unsigned int))
		);
		indexBuffer->Init();

		data.vertexArrayBuffer->SetIndexBuffer(indexBuffer);
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera) noexcept
	{
		data.shaderProgram->Bind();
		data.shaderProgram->SetUniformMat4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::DrawQuad(const Math::Vector2& position, const Math::Vector2& size, const Math::Vector4& color) noexcept
	{
		DrawQuad(Math::Vector3(position.x, position.y, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector2& size, const Math::Vector4& color) noexcept
	{
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), Math::Vector3(size.x, size.y, 1.0f));

		data.shaderProgram->SetUniformMat4("u_ModelMatrix", modelMatrix);
		data.shaderProgram->SetUniformFloat4("u_Color", color);

		data.vertexArrayBuffer->Bind();
		Renderer::DrawTriangles(data.vertexArrayBuffer);
	}

	void Renderer2D::EndScene() noexcept
	{
		data.vertexArrayBuffer->Unbind();
		data.shaderProgram->Unbind();
	}

	void Renderer2D::Destroy() noexcept
	{
		data.vertexArrayBuffer->Destroy();
		data.shaderProgram->Destroy();
	}

}