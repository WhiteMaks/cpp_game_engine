#include "WebGLVertexStaticBuffer.h"

namespace GraphicsEngine
{
	
	WebGLVertexStaticBuffer::WebGLVertexStaticBuffer(float* vertices, unsigned int size) noexcept
		: VertexStaticBuffer(vertices, size), buffer(0)
	{
	}

	void WebGLVertexStaticBuffer::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization webGL static vertex buffer has started");
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		GRAPHICS_ENGINE_INFO("Initialization webGL static vertex buffer completed");
	}

	void WebGLVertexStaticBuffer::Bind() noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
	}

	void WebGLVertexStaticBuffer::Unbind() noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void WebGLVertexStaticBuffer::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction webGL static vertex buffer has started");
		glDeleteBuffers(1, &buffer);
		GRAPHICS_ENGINE_INFO("Destruction webGL static vertex buffer completed");
	}

}