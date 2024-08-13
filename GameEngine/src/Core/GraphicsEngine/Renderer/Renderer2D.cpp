#include "Core/GraphicsEngine/Renderer/Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "Core/GraphicsEngine/Renderer/Renderer.h"
#include "Core/GraphicsEngine/Assets/ShaderProgramFactory.h"
#include "Core/GraphicsEngine/Assets/TextureFactory.h"
#include "Core/GraphicsEngine/Renderer/Buffers/BufferFactory.h"

namespace GraphicsEngine
{
	struct Quad
	{
		Math::Vector3 position;
		Math::Vector4 color;
		Math::Vector2 textureCoordinate;
		float textureIndex;
	};

	struct Data
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		static const unsigned int batchTextureSlots = 32;
#elif GAME_ENGINE_PLATFORM_BROWSER
		static const unsigned int batchTextureSlots = 16;
#endif
		static const unsigned int batchQuadsSize = 10000;
		static const unsigned int batchVerticesSize = batchQuadsSize * 4;
		static const unsigned int batchIndicesSize = batchQuadsSize * 6;

		std::shared_ptr<ShaderProgram> shaderProgram;
		std::shared_ptr<VertexDynamicBuffer> vertexDynamicBuffer;
		std::shared_ptr<VertexArrayBuffer> vertexArrayBuffer;

		std::shared_ptr<Texture> whiteTexture;
		Math::Vector4 whiteColor;

		unsigned int quadIndexCount = 0;

		std::array<std::shared_ptr<Texture>, batchTextureSlots> textureSlots;
		unsigned int textureSlotIndex = 0;

		Quad* quadBuffer = nullptr;
		Quad* quadBufferPtr = nullptr;
	};

	static Data data;

	glm::mat4 Renderer2D::viewProjectionMatrix = glm::mat4(1.0f);

	void Renderer2D::Init() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Initialization 2D renderer has started");
		data.vertexArrayBuffer = std::shared_ptr<VertexArrayBuffer>(
			BufferFactory::CreateVertexArrayBuffer()
		);
		data.vertexArrayBuffer->Init();

		data.vertexDynamicBuffer = std::shared_ptr<VertexDynamicBuffer>(
			BufferFactory::CreateVertexDynamicBuffer(data.batchVerticesSize * sizeof(Quad))
		);

		std::vector<BufferElement> bufferElements = {
			{BufferElementType::FLOAT_3, "a_Position"},
			{BufferElementType::FLOAT_4, "a_Color"},
			{BufferElementType::FLOAT_2, "a_TextureCoordinate"},
			{BufferElementType::FLOAT, "a_TextureIndex"},
		};

		BufferLayout bufferLayout(bufferElements);
		bufferLayout.Init();

		data.vertexDynamicBuffer->SetLayout(bufferLayout);
		data.vertexDynamicBuffer->Init();

		data.vertexArrayBuffer->AddVertexBuffer(data.vertexDynamicBuffer);

		data.quadBuffer = new Quad[data.batchVerticesSize];

		unsigned int offset = 0;
		unsigned int* quadIndices = new unsigned int[data.batchIndicesSize];
		for (unsigned int i = 0; i + 5 < data.batchIndicesSize; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		std::shared_ptr<IndexStaticBuffer> indexBuffer = std::shared_ptr<IndexStaticBuffer>(
			BufferFactory::CreateIndexStaticBuffer(quadIndices, data.batchIndicesSize)
		);
		indexBuffer->Init();
		delete[] quadIndices;

		data.vertexArrayBuffer->SetIndexBuffer(indexBuffer);

		data.whiteColor = Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		unsigned int whiteColorData = 0xffffffff;
		data.whiteTexture = std::shared_ptr<Texture>(
			TextureFactory::Create(1, 1)
		);
		data.whiteTexture->Init();
		data.whiteTexture->SetData(&whiteColorData);

		data.textureSlots[data.textureSlotIndex] = data.whiteTexture;
		data.textureSlotIndex++;

		int samplers[data.batchTextureSlots];
		for (unsigned int i = 0; i < data.batchTextureSlots; i++)
		{
			samplers[i] = i;
		}

		data.shaderProgram = std::shared_ptr<ShaderProgram>(
			ShaderProgramFactory::Create("assets/shaders/default_2d_shader")
		);
		data.shaderProgram->Init();
		data.shaderProgram->Bind();
		data.shaderProgram->SetUniformInts("u_Textures", samplers, data.batchTextureSlots);
		GRAPHICS_ENGINE_DEBUG("Initialization 2D renderer completed");
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera) noexcept
	{
		data.shaderProgram->Bind();
		data.vertexArrayBuffer->Bind();

		data.shaderProgram->SetUniformMat4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
		
		data.quadIndexCount = 0;
		data.quadBufferPtr = data.quadBuffer;

		//data.textureSlotIndex = 1;
	}

	void Renderer2D::DrawQuad(const Math::Vector2& position, const Math::Vector2& scale, const Math::Vector4& color) noexcept
	{
		DrawQuad(position, Math::Vector3(0.0f), scale, color, data.whiteTexture);
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector2& scale, const Math::Vector4& color) noexcept
	{
		DrawQuad(position, Math::Vector3(0.0f), scale, color, data.whiteTexture);
	}

	void Renderer2D::DrawQuad(const Math::Vector2& position, const Math::Vector2& scale, const std::shared_ptr<Texture>& texture) noexcept
	{
		DrawQuad(position, Math::Vector3(0.0f), scale, data.whiteColor,  texture);
	}

	void Renderer2D::DrawQuad(const Math::Vector2& position, const Math::Vector3& rotation, const Math::Vector2& scale, const Math::Vector4& color) noexcept
	{
		DrawQuad(position, rotation, scale, color, data.whiteTexture);
	}

	void Renderer2D::DrawQuad(const Math::Vector2& position, const Math::Vector3& rotation, const Math::Vector2& scale, const std::shared_ptr<Texture>& texture) noexcept
	{
		DrawQuad(position, Math::Vector3(0.0f), scale, data.whiteColor, texture);
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector2& scale, const std::shared_ptr<Texture>& texture) noexcept
	{
		DrawQuad(position, Math::Vector3(0.0f), scale, data.whiteColor, texture);
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector2& scale, const Math::Vector4& color) noexcept
	{
		DrawQuad(position, rotation, scale, color, data.whiteTexture);
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector2& scale, const std::shared_ptr<Texture>& texture) noexcept
	{
		DrawQuad(position, rotation, scale, data.whiteColor, texture);
	}

	void Renderer2D::EndScene() noexcept
	{
		unsigned int dataSize = (uint8_t*) data.quadBufferPtr - (uint8_t*) data.quadBuffer;
		data.vertexDynamicBuffer->SetData(data.quadBuffer, dataSize);
		
		data.vertexArrayBuffer->Bind();

		Flush();

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

	void Renderer2D::DrawQuad(const Math::Vector2& position, const Math::Vector3& rotation, const Math::Vector2& scale, const Math::Vector4& color, const std::shared_ptr<Texture>& texture) noexcept
	{
		DrawQuad(Math::Vector3(position.x, position.y, 0.0f), rotation, scale, color, texture);
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector2& scale, const Math::Vector4& color, const std::shared_ptr<Texture>& texture) noexcept
	{
		float textureIndex = -1.0f;

		for (unsigned int i = 0; i < data.textureSlotIndex; i++)
		{
			if (*data.textureSlots[i].get() == *texture.get())
			{
				textureIndex = i;
				break;
			}
		}

		if (textureIndex == -1.0f)
		{
			textureIndex = data.textureSlotIndex;
			data.textureSlots[data.textureSlotIndex] = texture;

			data.textureSlotIndex++;
		}

		data.quadBufferPtr->position = position;
		data.quadBufferPtr->color = color;
		data.quadBufferPtr->textureCoordinate = {0.0f, 0.0f};
		data.quadBufferPtr->textureIndex = textureIndex;
		data.quadBufferPtr++;

		data.quadBufferPtr->position = {position.x + scale.x, position.y, position.z};
		data.quadBufferPtr->color = color;
		data.quadBufferPtr->textureCoordinate = {1.0f, 0.0f};
		data.quadBufferPtr->textureIndex = textureIndex;
		data.quadBufferPtr++;

		data.quadBufferPtr->position = {position.x + scale.x, position.y + scale.y, position.z};
		data.quadBufferPtr->color = color;
		data.quadBufferPtr->textureCoordinate = {1.0f, 1.0f};
		data.quadBufferPtr->textureIndex = textureIndex;
		data.quadBufferPtr++;

		data.quadBufferPtr->position = {position.x, position.y + scale.y, position.z};
		data.quadBufferPtr->color = color;
		data.quadBufferPtr->textureCoordinate = {0.0f, 1.0f};
		data.quadBufferPtr->textureIndex = textureIndex;
		data.quadBufferPtr++;

		data.quadIndexCount += 6;
	}

	void Renderer2D::Flush() noexcept
	{
		for (unsigned int i = 0; i < data.textureSlotIndex; i++)
		{
			data.textureSlots[i]->Bind(i);
		}

		Renderer::DrawTriangles(data.quadIndexCount);
	}

}