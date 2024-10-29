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
		float textureIndex = 0;
	};

	struct Data
	{
#ifdef GAME_ENGINE_PLATFORM_WINDOWS
		static const unsigned int batchTextureSlots = 32;
#elif GAME_ENGINE_PLATFORM_BROWSER
		static const unsigned int batchTextureSlots = 16;
#endif
		const unsigned int batchQuadsSize = 10000;
		const unsigned int batchVerticesSize = batchQuadsSize * 4;
		const unsigned int batchIndicesSize = batchQuadsSize * 6;

		const glm::mat4 identityMatrix = glm::mat4(1.0f);
		
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

		Math::Vector4 quadVertexPositions[4];
		Math::Vector2 quadTextureCoordinates[4];
	};

	static Data data;

	void Renderer2D::Init() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Initialization 2D renderer has started");
		InitBuffers();
		InitAssets();
		InitQuadData();
		GRAPHICS_ENGINE_DEBUG("Initialization 2D renderer completed");
	}

	void Renderer2D::BeginScene(Camera& camera) noexcept
	{
		data.shaderProgram->Bind();
		data.vertexArrayBuffer->Bind();

		data.shaderProgram->SetUniformMat4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());

		ResetBatchData();
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector3& scale, const Math::Vector4& color) noexcept
	{
		DrawQuad(position, Math::Vector3(0.0f), scale, color, data.whiteTexture, data.quadTextureCoordinates);
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector3& scale, const Math::Vector4& color) noexcept
	{
		DrawQuad(position, rotation, scale, color, data.whiteTexture, data.quadTextureCoordinates);
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector3& scale, const std::shared_ptr<Texture>& texture) noexcept
	{
		DrawQuad(position, Math::Vector3(0.0f), scale, data.whiteColor, texture, data.quadTextureCoordinates);
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector3& scale, const std::shared_ptr<Texture>& texture) noexcept
	{
		DrawQuad(position, Math::Vector3(0.0f), scale, data.whiteColor, texture, data.quadTextureCoordinates);
	}

	void Renderer2D::DrawSprite(const Math::Vector3& position, const Math::Vector3& scale, const std::shared_ptr<Sprite>& sprite) noexcept
	{
		DrawQuad(position, Math::Vector3(0.0f), scale, data.whiteColor, sprite->GetTexture(), sprite->GetTextureCoordinates());
	}

	void Renderer2D::DrawSprite(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector3& scale, const std::shared_ptr<Sprite>& sprite) noexcept
	{
		DrawQuad(position, rotation, scale, data.whiteColor, sprite->GetTexture(), sprite->GetTextureCoordinates());
	}

	void Renderer2D::EndScene() noexcept
	{
		unsigned int dataSize = (uint8_t*) data.quadBufferPtr - (uint8_t*) data.quadBuffer;
		data.vertexDynamicBuffer->SetData(data.quadBuffer, dataSize);
		
		data.vertexArrayBuffer->Bind();

		Flush();
	}

	void Renderer2D::Destroy() noexcept
	{
		GRAPHICS_ENGINE_DEBUG("Destruction 2D renderer has started");
		data.vertexDynamicBuffer->Destroy();
		data.vertexArrayBuffer->Destroy();
		data.whiteTexture->Destroy();
		for (unsigned int i = 0; i < data.textureSlotIndex; i++)
		{
			data.textureSlots[i]->Destroy();
		}
		data.shaderProgram->Destroy();
		GRAPHICS_ENGINE_DEBUG("Destruction 2D renderer completed");
	}

	void Renderer2D::DrawQuad(const Math::Vector3& position, const Math::Vector3& rotation, const Math::Vector3& scale, const Math::Vector4& color, const std::shared_ptr<Texture>& texture, const Math::Vector2* textureCoordinates) noexcept
	{
		if (data.quadIndexCount >= data.batchIndicesSize)
		{
			StartNewBatch();
		}

		float textureSlotIndex = -1.0f;

		for (unsigned int i = 0; i < data.textureSlotIndex; i++)
		{
			if (*data.textureSlots[i].get() == *texture.get())
			{
				textureSlotIndex = i;
				break;
			}
		}

		if (textureSlotIndex == -1.0f)
		{
			textureSlotIndex = data.textureSlotIndex;
			data.textureSlots[data.textureSlotIndex] = texture;

			data.textureSlotIndex++;
		}

		glm::mat4 modelMatrix = glm::translate(data.identityMatrix, position)
			* glm::rotate(data.identityMatrix, glm::radians(rotation.x), Math::Vector3(1.0f, 0.0f, 0.0f))
			* glm::rotate(data.identityMatrix, glm::radians(rotation.y), Math::Vector3(0.0f, 1.0f, 0.0f))
			* glm::rotate(data.identityMatrix, glm::radians(rotation.z), Math::Vector3(0.0f, 0.0f, 1.0f))
			* glm::scale(data.identityMatrix, scale);

		glm::vec4 blPosition = modelMatrix * data.quadVertexPositions[0];
		glm::vec4 brPosition = modelMatrix * data.quadVertexPositions[1];
		glm::vec4 trPosition = modelMatrix * data.quadVertexPositions[2];
		glm::vec4 tlPosition = modelMatrix * data.quadVertexPositions[3];

		FillQuadBufferPtr(Math::Vector3(blPosition.x, blPosition.y, blPosition.z), color, textureCoordinates[0], textureSlotIndex);
		FillQuadBufferPtr(Math::Vector3(brPosition.x, brPosition.y, brPosition.z), color, textureCoordinates[1], textureSlotIndex);
		FillQuadBufferPtr(Math::Vector3(trPosition.x, trPosition.y, trPosition.z), color, textureCoordinates[2], textureSlotIndex);
		FillQuadBufferPtr(Math::Vector3(tlPosition.x, tlPosition.y, tlPosition.z), color, textureCoordinates[3], textureSlotIndex);

		data.quadIndexCount += 6;
	}

	void Renderer2D::FillQuadBufferPtr(const Math::Vector3& position, const Math::Vector4& color, const Math::Vector2& textureCoordinate, float textureIndex)
	{
		data.quadBufferPtr->position = position;
		data.quadBufferPtr->color = color;
		data.quadBufferPtr->textureCoordinate = textureCoordinate;
		data.quadBufferPtr->textureIndex = textureIndex;

		data.quadBufferPtr++;
	}

	void Renderer2D::Flush() noexcept
	{
		for (unsigned int i = 0; i < data.textureSlotIndex; i++)
		{
			data.textureSlots[i]->Bind(i);
		}

		Renderer::DrawTriangles(data.quadIndexCount);
	}

	void Renderer2D::StartNewBatch() noexcept
	{
		EndScene();
		ResetBatchData();
	}

	void Renderer2D::ResetBatchData() noexcept
	{
		data.quadIndexCount = 0;
		data.quadBufferPtr = data.quadBuffer;
		//data.textureSlotIndex = 1;
	}

	void Renderer2D::InitBuffers() noexcept
	{
		data.vertexArrayBuffer = BufferFactory::CreateVertexArrayBuffer();
		data.vertexArrayBuffer->Init();

		data.vertexDynamicBuffer = BufferFactory::CreateVertexDynamicBuffer(data.batchVerticesSize * sizeof(Quad));

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
		for (unsigned int i = 0; i < data.batchIndicesSize; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		std::shared_ptr<IndexStaticBuffer> indexBuffer = BufferFactory::CreateIndexStaticBuffer(quadIndices, data.batchIndicesSize);
		indexBuffer->Init();
		delete[] quadIndices;

		data.vertexArrayBuffer->SetIndexBuffer(indexBuffer);
	}

	void Renderer2D::InitAssets() noexcept
	{
		data.whiteColor = Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		unsigned int whiteColorData = 0xffffffff;
		data.whiteTexture = TextureFactory::Create(1, 1);
		data.whiteTexture->Init();
		data.whiteTexture->SetData(&whiteColorData);

		data.textureSlots[data.textureSlotIndex] = data.whiteTexture;
		data.textureSlotIndex++;

		int samplers[data.batchTextureSlots];
		for (unsigned int i = 0; i < data.batchTextureSlots; i++)
		{
			samplers[i] = i;
		}

		data.shaderProgram = ShaderProgramFactory::Create("assets/shaders/default_2d_shader");
		data.shaderProgram->Init();
		data.shaderProgram->Bind();
		data.shaderProgram->SetUniformInts("u_Textures", samplers, data.batchTextureSlots);
	}

	void Renderer2D::InitQuadData() noexcept
	{
		data.quadVertexPositions[0] = Math::Vector4(-0.5f, -0.5f, 0.0f, 1.0f);
		data.quadVertexPositions[1] = Math::Vector4( 0.5f, -0.5f, 0.0f, 1.0f);
		data.quadVertexPositions[2] = Math::Vector4( 0.5f,  0.5f, 0.0f, 1.0f);
		data.quadVertexPositions[3] = Math::Vector4(-0.5f,  0.5f, 0.0f, 1.0f);

		data.quadTextureCoordinates[0] = Math::Vector2(0.0f, 0.0f);
		data.quadTextureCoordinates[1] = Math::Vector2(1.0f, 0.0f);
		data.quadTextureCoordinates[2] = Math::Vector2(1.0f, 1.0f);
		data.quadTextureCoordinates[3] = Math::Vector2(0.0f, 1.0f);
	}

}