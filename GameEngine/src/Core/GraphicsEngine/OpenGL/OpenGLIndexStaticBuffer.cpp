#include "OpenGLIndexStaticBuffer.h"

namespace GraphicsEngine
{

	OpenGLIndexStaticBuffer::OpenGLIndexStaticBuffer(unsigned int* indeces, unsigned int count) noexcept
		: IndexStaticBuffer(indeces, count), buffer(0)
	{
	}

	void OpenGLIndexStaticBuffer::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization openGL index buffer has started");
		glCreateBuffers(1, &buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indeces, GL_STATIC_DRAW);
		GRAPHICS_ENGINE_INFO("Initialization openGL index buffer completed");
	}

	void OpenGLIndexStaticBuffer::Bind() noexcept
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	}

	void OpenGLIndexStaticBuffer::Unbind() noexcept
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLIndexStaticBuffer::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction openGL index buffer has started");
		glDeleteBuffers(1, &buffer);
		GRAPHICS_ENGINE_INFO("Destruction openGL index buffer completed");
	}

}