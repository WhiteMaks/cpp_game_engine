#include "Core/GraphicsEngine/Renderer/Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "Core/GraphicsEngine/Renderer/Renderer.h"
#include "Core/GraphicsEngine/Assets/ShaderProgramFactory.h"
#include "Core/GraphicsEngine/Assets/TextureFactory.h"
#include "Core/GraphicsEngine/Renderer/Buffers/BufferFactory.h"

namespace GraphicsEngine
{
	struct Data
	{
		std::shared_ptr<ShaderProgram> shaderProgram;
		std::shared_ptr<VertexArrayBuffer> vertexArrayBuffer;

		std::shared_ptr<Texture> whiteTexture;
		Math::Vector4 whiteColor;
	};

	static Data data;

	glm::mat4 Renderer2D::viewProjectionMatrix = glm::mat4(1.0f);

	void Renderer2D::Init() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Initialization 2D renderer has started");
		data.shaderProgram = std::shared_ptr<ShaderProgram>(
			ShaderProgramFactory::Create("assets/shaders/default_2d_shader")
		);
		data.shaderProgram->Init();
		data.shaderProgram->Bind();
		data.shaderProgram->SetUniformInt("u_Texture", 0);

		data.vertexArrayBuffer = std::shared_ptr<VertexArrayBuffer>(
			BufferFactory::CreateVertexArrayBuffer()
		);
		data.vertexArrayBuffer->Init();
		
		float vertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		std::shared_ptr<VertexStaticBuffer> vertexBuffer = std::shared_ptr<VertexStaticBuffer>(
			BufferFactory::CreateVertexStaticBuffer(vertices, sizeof(vertices))
		);

		std::vector<BufferElement> bufferElements = {
			{BufferElementType::FLOAT_3, "a_Position"},
			{BufferElementType::FLOAT_2, "a_TextureCoordinate"},
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

		data.whiteColor = Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		unsigned int whiteColorData = 0xffffffff;
		data.whiteTexture = std::shared_ptr<Texture>(
			TextureFactory::Create(1, 1)
		);
		data.whiteTexture->Init();
		data.whiteTexture->SetData(&whiteColorData);
		GRAPHICS_ENGINE_DEBUG("Initialization 2D renderer completed");
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera) noexcept
	{
		data.shaderProgram->Bind();
		data.vertexArrayBuffer->Bind();

		data.shaderProgram->SetUniformMat4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::DrawQuad(const Math::Vector2& position, const Math::Vector2& scale, const Math::Vector4& color) noexcept
	{
		DrawQuad(position, Math::Vector3(0.0f), scale, data.whiteTexture, color);
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector2& scale, const Math::Vector4& color) noexcept
	{
		DrawQuad(position, Math::Vector3(0.0f), scale, data.whiteTexture, color);
	}

	void Renderer2D::DrawQuad(const Math::Vector2& position, const Math::Vector2& scale, const std::shared_ptr<Texture>& texture) noexcept
	{
		DrawQuad(position, Math::Vector3(0.0f), scale, texture, data.whiteColor);
	}

	void Renderer2D::DrawQuad(const Math::Vector2& position, const Math::Vector3& rotation, const Math::Vector2& scale, const Math::Vector4& color) noexcept
	{
		DrawQuad(position, rotation, scale, data.whiteTexture, color);
	}

	void Renderer2D::DrawQuad(const Math::Vector2& position, const Math::Vector3& rotation, const Math::Vector2& scale, const std::shared_ptr<Texture>& texture) noexcept
	{
		DrawQuad(position, Math::Vector3(0.0f), scale, texture, data.whiteColor);
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector2& scale, const std::shared_ptr<Texture>& texture) noexcept
	{
		DrawQuad(position, Math::Vector3(0.0f), scale, texture, data.whiteColor);
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector2& scale, const Math::Vector4& color) noexcept
	{
		DrawQuad(position, rotation, scale, data.whiteTexture, color);
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector2& scale, const std::shared_ptr<Texture>& texture) noexcept
	{
		DrawQuad(position, rotation, scale, texture, data.whiteColor);
	}

	void Renderer2D::EndScene() noexcept
	{
		data.vertexArrayBuffer->Unbind();
		data.shaderProgram->Unbind();
	}

	void Renderer2D::Destroy() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Destruction 2D renderer has started");
		data.vertexArrayBuffer->Destroy();
		data.whiteTexture->Destroy();
		data.shaderProgram->Destroy();
		GRAPHICS_ENGINE_DEBUG("Destruction 2D renderer completed");
	}

	void Renderer2D::DrawQuad(const Math::Vector2& position, const Math::Vector3& rotation, const Math::Vector2& scale, const std::shared_ptr<Texture>& texture, const Math::Vector4& color) noexcept
	{
		DrawQuad(Math::Vector3(position.x, position.y, 0.0f), rotation, scale, texture, color);
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector2& scale, const std::shared_ptr<Texture>& texture, const Math::Vector4& color) noexcept
	{
		texture->Bind();

		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position) 
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::scale(glm::mat4(1.0f), Math::Vector3(scale.x, scale.y, 1.0f));

		data.shaderProgram->SetUniformMat4("u_ModelMatrix", modelMatrix);
		data.shaderProgram->SetUniformFloat4("u_Color", color);

		Renderer::DrawTriangles(data.vertexArrayBuffer);

		texture->Unbind();
	}

}