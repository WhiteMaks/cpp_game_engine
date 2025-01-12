#include "WebGLGraphicsLibrary.h"

#include "WebGLContext.h"
#include "Core/Platform/Browser/BrowserWindow.h"
#include "WebGLRenderer.h"
#include "WebGLShaderProgram.h"
#include "WebGLTexture.h"
#include "WebGLFrameBuffer.h"
#include "WebGLIndexStaticBuffer.h"
#include "WebGLVertexArrayBuffer.h"
#include "WebGLVertexDynamicBuffer.h"
#include "WebGLVertexStaticBuffer.h"

namespace GraphicsEngine
{

	std::shared_ptr<GraphicsContext> WebGLGraphicsLibrary::CreateContext() noexcept
	{
		return std::shared_ptr<GraphicsContext>(new WebGLContext(Platform::BrowserWindow::window));
	}

	std::shared_ptr<RendererAPI> WebGLGraphicsLibrary::CreateRenderer() noexcept
	{
		return std::shared_ptr<RendererAPI>(new WebGLRenderer());
	}

	std::shared_ptr<ShaderProgram> WebGLGraphicsLibrary::CreateShaderProgram(const std::string& filepath) noexcept
	{
		return std::shared_ptr<ShaderProgram>(new WebGLShaderProgram(filepath));
	}

	std::shared_ptr<ShaderProgram> WebGLGraphicsLibrary::CreateShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) noexcept
	{
		return std::shared_ptr<ShaderProgram>(new WebGLShaderProgram(vertexShaderCode, fragmentShaderCode));
	}

	std::shared_ptr<Texture> WebGLGraphicsLibrary::CreateTexture(const unsigned int width, const unsigned int height) noexcept
	{
		return std::shared_ptr<Texture>(new WebGLTexture(width, height));
	}

	std::shared_ptr<Texture> WebGLGraphicsLibrary::CreateTexture(const std::string& pathToTexture) noexcept
	{
		return std::shared_ptr<Texture>(new WebGLTexture(pathToTexture));
	}

	std::shared_ptr<FrameBuffer> WebGLGraphicsLibrary::CreateFrameBuffer(const FrameBufferData& data) noexcept
	{
		return std::shared_ptr<FrameBuffer>(new WebGLFrameBuffer(data));
	}

	std::shared_ptr<IndexStaticBuffer> WebGLGraphicsLibrary::CreateIndexStaticBuffer(unsigned int* indices, unsigned int count) noexcept
	{
		return std::shared_ptr<IndexStaticBuffer>(new WebGLIndexStaticBuffer(indices, count));
	}

	std::shared_ptr<VertexArrayBuffer> WebGLGraphicsLibrary::CreateVertexArrayBuffer() noexcept
	{
		return std::shared_ptr<VertexArrayBuffer>(new WebGLVertexArrayBuffer());
	}

	std::shared_ptr<VertexDynamicBuffer> WebGLGraphicsLibrary::CreateVertexDynamicBuffer(unsigned int size) noexcept
	{
		return std::shared_ptr<VertexDynamicBuffer>(new WebGLVertexDynamicBuffer(size));
	}

	std::shared_ptr<VertexStaticBuffer> WebGLGraphicsLibrary::CreateVertexStaticBuffer(float* vertices, unsigned int size) noexcept
	{
		return std::shared_ptr<VertexStaticBuffer>(new WebGLVertexStaticBuffer(vertices, size));
	}

}