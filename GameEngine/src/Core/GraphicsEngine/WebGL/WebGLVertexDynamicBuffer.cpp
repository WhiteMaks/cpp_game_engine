#include "WebGLVertexDynamicBuffer.h"

namespace GraphicsEngine
{
	
	WebGLVertexDynamicBuffer::WebGLVertexDynamicBuffer(unsigned int size) noexcept
		: VertexDynamicBuffer(size), buffer(0)
	{
	}

	void WebGLVertexDynamicBuffer::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization webGL dynamic vertex buffer has started");
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		GRAPHICS_ENGINE_INFO("Initialization webGL dynamic vertex buffer completed");
	}

	void WebGLVertexDynamicBuffer::Bind() noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
	}

	void WebGLVertexDynamicBuffer::Unbind() noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void WebGLVertexDynamicBuffer::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction webGL dynamic vertex buffer has started");
		glDeleteBuffers(1, &buffer);
		GRAPHICS_ENGINE_INFO("Destruction webGL dynamic vertex buffer completed");
	}

	void WebGLVertexDynamicBuffer::SetData(const void* data, unsigned int size) noexcept
	{
		Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

}