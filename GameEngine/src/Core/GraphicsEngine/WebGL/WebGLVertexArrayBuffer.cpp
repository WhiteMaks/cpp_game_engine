#include "WebGLVertexArrayBuffer.h"

namespace GraphicsEngine
{
	
	WebGLVertexArrayBuffer::WebGLVertexArrayBuffer() noexcept
		: buffer(0)
	{
	}

	void WebGLVertexArrayBuffer::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization webGL vertex array buffer has started");
		glGenVertexArrays(1, &buffer);
		glBindVertexArray(buffer);
		GRAPHICS_ENGINE_INFO("Initialization webGL vertex array buffer completed");
	}

	void WebGLVertexArrayBuffer::Bind() noexcept
	{
		glBindVertexArray(buffer);
	}

	void WebGLVertexArrayBuffer::Unbind() noexcept
	{
		glBindVertexArray(0);
	}

	void WebGLVertexArrayBuffer::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction webGL vertex array buffer has started");
		glDeleteVertexArrays(1, &buffer);

		for (std::shared_ptr<VertexStaticBuffer> vertexStaticBuffer : vertexStaticBuffers)
		{
			vertexStaticBuffer->Destroy();
		}

		indexStaticBuffer->Destroy();
		GRAPHICS_ENGINE_INFO("Destruction webGL vertex array buffer completed");
	}

	void WebGLVertexArrayBuffer::AddVertexBuffer(std::shared_ptr<VertexStaticBuffer>& buffer) noexcept
	{
		if (buffer->GetLayout().GetElements().size() <= 0)
		{
			GRAPHICS_ENGINE_CRITICAL("Buffer layout not initialized");
			exit(GameEngine::VERTEX_ARRAY_BUFFER_INITIALIZAATION_FAILED);
		}

		glBindVertexArray(this->buffer);
		buffer->Bind();

		BufferLayout& layout = buffer->GetLayout();

		unsigned int index = 0;
		for (auto& element : layout.GetElements())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetCount(), ConvertBufferElementTypeToWebGL(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			index++;
		}

		vertexStaticBuffers.push_back(buffer);
		GRAPHICS_ENGINE_INFO("New vertex static buffer saved into vertex array buffer. Ready [{0}] vertex static buffers to use", vertexStaticBuffers.size());
	}

	void WebGLVertexArrayBuffer::SetIndexBuffer(std::shared_ptr<IndexStaticBuffer>& buffer) noexcept
	{
		glBindVertexArray(this->buffer);
		buffer->Bind();

		indexStaticBuffer = buffer;
		GRAPHICS_ENGINE_INFO("Index static buffer saved into vertex array buffer");
	}

	GLenum WebGLVertexArrayBuffer::ConvertBufferElementTypeToWebGL(BufferElementType type) noexcept
	{
		switch (type)
		{
		case GraphicsEngine::BufferElementType::FLOAT:
		case GraphicsEngine::BufferElementType::FLOAT_2:
		case GraphicsEngine::BufferElementType::FLOAT_3:
		case GraphicsEngine::BufferElementType::FLOAT_4:
		case GraphicsEngine::BufferElementType::MAT_2:
		case GraphicsEngine::BufferElementType::MAT_3:
		case GraphicsEngine::BufferElementType::MAT_4:
			return GL_FLOAT;
		case GraphicsEngine::BufferElementType::INT:
		case GraphicsEngine::BufferElementType::INT_2:
		case GraphicsEngine::BufferElementType::INT_3:
		case GraphicsEngine::BufferElementType::INT_4:
			return GL_INT;
		case GraphicsEngine::BufferElementType::BOOL:
			return GL_BOOL;
		}

		GRAPHICS_ENGINE_CRITICAL("Failed convert buffer element type to WebGL");
		exit(GameEngine::VERTEX_ARRAY_BUFFER_INITIALIZAATION_FAILED);
	}

}