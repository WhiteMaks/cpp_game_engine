#pragma once

#include <memory>

#include "Core/Core.h"

#include "GraphicsContext.h"
#include "RendererAPI.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "FrameBuffer.h"
#include "IndexStaticBuffer.h"
#include "VertexArrayBuffer.h"
#include "VertexDynamicBuffer.h"
#include "VertexStaticBuffer.h"
#include "Spritesheet.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API GraphicsLibrary
	{
	public:
		virtual std::shared_ptr<GraphicsContext> CreateContext() noexcept;
		virtual std::shared_ptr<RendererAPI> CreateRenderer() noexcept;
		virtual std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& filepath) noexcept;
		virtual std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) noexcept;
		virtual std::shared_ptr<Texture> CreateTexture(const unsigned int width, const unsigned int height) noexcept;
		virtual std::shared_ptr<Texture> CreateTexture(const std::string& pathToTexture) noexcept;
		virtual std::shared_ptr<FrameBuffer> CreateFrameBuffer(const FrameBufferData& data) noexcept;
		virtual std::shared_ptr<IndexStaticBuffer> CreateIndexStaticBuffer(unsigned int* indices, unsigned int count) noexcept;
		virtual std::shared_ptr<VertexArrayBuffer> CreateVertexArrayBuffer() noexcept;
		virtual std::shared_ptr<VertexDynamicBuffer> CreateVertexDynamicBuffer(unsigned int size) noexcept;
		virtual std::shared_ptr<VertexStaticBuffer> CreateVertexStaticBuffer(float* vertices, unsigned int size) noexcept;
		virtual std::shared_ptr<Spritesheet> CreateSpritesheet(const std::shared_ptr<Texture>& texture, const Math::Vector2& size) noexcept;
	};

}
