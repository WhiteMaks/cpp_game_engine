#include "OpenGLVertexBuffer.h"

namespace GraphicsEngine
{
	
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int size) noexcept
		: VertexBuffer(vertices, size), buffer(0)
	{
	}

	void OpenGLVertexBuffer::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization openGL vertex buffer has started");
		glCreateBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		GRAPHICS_ENGINE_INFO("Initialization openGL vertex buffer completed");
	}

	void OpenGLVertexBuffer::Bind() noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
	}

	void OpenGLVertexBuffer::Unbind() noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction openGL vertex buffer has started");
		glDeleteBuffers(1, &buffer);
		GRAPHICS_ENGINE_INFO("Destruction openGL vertex buffer completed");
	}

}