#include "OpenGLVertexDynamicBuffer.h"

namespace GraphicsEngine
{
	
	OpenGLVertexDynamicBuffer::OpenGLVertexDynamicBuffer(unsigned int size) noexcept
		: VertexDynamicBuffer(size), buffer(0)
	{
	}

	void OpenGLVertexDynamicBuffer::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization openGL dynamic vertex buffer has started");
		glCreateBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		GRAPHICS_ENGINE_INFO("Initialization openGL dynamic vertex buffer completed");
	}

	void OpenGLVertexDynamicBuffer::Bind() noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
	}

	void OpenGLVertexDynamicBuffer::Unbind() noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexDynamicBuffer::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction openGL dynamic vertex buffer has started");
		glDeleteBuffers(1, &buffer);
		GRAPHICS_ENGINE_INFO("Destruction openGL dynamic vertex buffer completed");
	}

	void OpenGLVertexDynamicBuffer::SetData(const void* data, unsigned int size) noexcept
	{
		Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

}