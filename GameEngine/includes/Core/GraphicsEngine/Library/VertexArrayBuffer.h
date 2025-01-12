#pragma once

#include <memory>
#include <vector>

#include "Core/Core.h"

#include "VertexStaticBuffer.h"
#include "VertexDynamicBuffer.h"
#include "IndexStaticBuffer.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API VertexArrayBuffer
	{
	protected:
		std::vector<std::shared_ptr<VertexStaticBuffer>> vertexStaticBuffers;
		std::vector<std::shared_ptr<VertexDynamicBuffer>> vertexDynamicBuffers;

		std::shared_ptr<IndexStaticBuffer> indexStaticBuffer;

	public:
		VertexArrayBuffer() noexcept;

	public:
		virtual void Init() noexcept;
		virtual void Bind() noexcept;
		virtual void Unbind() noexcept;
		virtual void Destroy() noexcept;

		virtual void AddVertexBuffer(std::shared_ptr<VertexStaticBuffer>& buffer) noexcept;
		virtual void AddVertexBuffer(std::shared_ptr<VertexDynamicBuffer>& buffer) noexcept;
		virtual void SetIndexBuffer(std::shared_ptr<IndexStaticBuffer>& buffer) noexcept;

		virtual std::vector<std::shared_ptr<VertexStaticBuffer>> GetVertexStaticBuffers() noexcept;
		virtual std::vector<std::shared_ptr<VertexDynamicBuffer>> GetVertexDynamicBuffers() noexcept;
		virtual std::shared_ptr<IndexStaticBuffer> GetIndexStaticBuffer() noexcept;

	};

}