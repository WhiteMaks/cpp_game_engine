#pragma once

#include <memory>

#include "Core/Core.h"

#include "GraphicsContext.h"
#include "Renderer.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "FrameBuffer.h"
#include "IndexStaticBuffer.h"
#include "VertexArrayBuffer.h"
#include "VertexDynamicBuffer.h"
#include "VertexStaticBuffer.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API GraphicsLibrary
	{
	public:
		virtual std::shared_ptr<GraphicsContext> CreateContext() noexcept;
		virtual std::shared_ptr<Renderer> CreateRenderer() noexcept;
		virtual std::shared_ptr<ShaderProgram> CreateShaderProgram() noexcept;
		virtual std::shared_ptr<Texture> CreateTexture() noexcept;
		virtual std::shared_ptr<FrameBuffer> CreateFrameBuffer() noexcept;
		virtual std::shared_ptr<IndexStaticBuffer> CreateIndexStaticBuffer() noexcept;
		virtual std::shared_ptr<VertexArrayBuffer> CreateVertexArrayBuffer() noexcept;
		virtual std::shared_ptr<VertexDynamicBuffer> CreateVertexDynamicBuffer() noexcept;
		virtual std::shared_ptr<VertexStaticBuffer> CreateVertexStaticBuffer() noexcept;
	};

}
