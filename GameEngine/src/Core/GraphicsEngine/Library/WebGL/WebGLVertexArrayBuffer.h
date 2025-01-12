#pragma once

#include <glad/glad.h>

#include "Core/GraphicsEngine/Library/VertexArrayBuffer.h"
#include "Tools/Log.h"
#include "ExitCodes.h"

namespace GraphicsEngine
{

	class WebGLVertexArrayBuffer : public VertexArrayBuffer
	{
	private:
		unsigned int buffer;

	public:
		WebGLVertexArrayBuffer() noexcept;

	public:
		void Init() noexcept override;
		void Bind() noexcept override;
		void Unbind() noexcept override;
		void Destroy() noexcept override;

		void AddVertexBuffer(std::shared_ptr<VertexStaticBuffer>& buffer) noexcept override;
		void AddVertexBuffer(std::shared_ptr<VertexDynamicBuffer>& buffer) noexcept override;
		void SetIndexBuffer(std::shared_ptr<IndexStaticBuffer>& buffer) noexcept override;

	private:
		GLenum ConvertBufferElementTypeToWebGL(BufferElementType type) noexcept;
	};

}