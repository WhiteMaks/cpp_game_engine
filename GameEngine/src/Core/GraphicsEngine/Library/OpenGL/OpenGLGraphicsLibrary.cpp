#include "OpenGLGraphicsLibrary.h"

#include "OpenGLContext.h"
#include "Core/Platform/Glfw/GlfwWindow.h"
#include "OpenGLRenderer.h"
#include "OpenGLShaderProgram.h"
#include "OpenGLTexture.h"
#include "OpenGLFrameBuffer.h"
#include "OpenGLIndexStaticBuffer.h"
#include "OpenGLVertexArrayBuffer.h"
#include "OpenGLVertexDynamicBuffer.h"
#include "OpenGLVertexStaticBuffer.h"

namespace GraphicsEngine
{

	std::shared_ptr<GraphicsContext> OpenGLGraphicsLibrary::CreateContext() noexcept
	{
		return std::shared_ptr<GraphicsContext>(new OpenGLContext(Platform::GlfwWindow::window));
	}

	std::shared_ptr<RendererAPI> OpenGLGraphicsLibrary::CreateRenderer() noexcept
	{
		return std::shared_ptr<RendererAPI>(new OpenGLRenderer());
	}

	std::shared_ptr<ShaderProgram> OpenGLGraphicsLibrary::CreateShaderProgram(const std::string& filepath) noexcept
	{
		return std::shared_ptr<ShaderProgram>(new OpenGLShaderProgram(filepath));
	}

	std::shared_ptr<ShaderProgram> OpenGLGraphicsLibrary::CreateShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) noexcept
	{
		return std::shared_ptr<ShaderProgram>(new OpenGLShaderProgram(vertexShaderCode, fragmentShaderCode));
	}

	std::shared_ptr<Texture> OpenGLGraphicsLibrary::CreateTexture(const unsigned int width, const unsigned int height) noexcept
	{
		return std::shared_ptr<Texture>(new OpenGLTexture(width, height));
	}

	std::shared_ptr<Texture> OpenGLGraphicsLibrary::CreateTexture(const std::string& pathToTexture) noexcept
	{
		return std::shared_ptr<Texture>(new OpenGLTexture(pathToTexture));
	}

	std::shared_ptr<FrameBuffer> OpenGLGraphicsLibrary::CreateFrameBuffer(const FrameBufferData& data) noexcept
	{
		return std::shared_ptr<FrameBuffer>(new OpenGLFrameBuffer(data));
	}

	std::shared_ptr<IndexStaticBuffer> OpenGLGraphicsLibrary::CreateIndexStaticBuffer(unsigned int* indices, unsigned int count) noexcept
	{
		return std::shared_ptr<IndexStaticBuffer>(new OpenGLIndexStaticBuffer(indices, count));
	}

	std::shared_ptr<VertexArrayBuffer> OpenGLGraphicsLibrary::CreateVertexArrayBuffer() noexcept
	{
		return std::shared_ptr<VertexArrayBuffer>(new OpenGLVertexArrayBuffer());
	}

	std::shared_ptr<VertexDynamicBuffer> OpenGLGraphicsLibrary::CreateVertexDynamicBuffer(unsigned int size) noexcept
	{
		return std::shared_ptr<VertexDynamicBuffer>(new OpenGLVertexDynamicBuffer(size));
	}

	std::shared_ptr<VertexStaticBuffer> OpenGLGraphicsLibrary::CreateVertexStaticBuffer(float* vertices, unsigned int size) noexcept
	{
		return std::shared_ptr<VertexStaticBuffer>(new OpenGLVertexStaticBuffer(vertices, size));
	}

}