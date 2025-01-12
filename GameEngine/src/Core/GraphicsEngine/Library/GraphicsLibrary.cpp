#include "Core/GraphicsEngine/Library/GraphicsLibrary.h"

namespace GraphicsEngine
{

	std::shared_ptr<GraphicsContext> GraphicsLibrary::CreateContext() noexcept
	{
		return std::shared_ptr<GraphicsContext>(new GraphicsContext());
	}

	std::shared_ptr<RendererAPI> GraphicsLibrary::CreateRenderer() noexcept
	{
		return std::shared_ptr<RendererAPI>(new RendererAPI());
	}

	std::shared_ptr<ShaderProgram> GraphicsLibrary::CreateShaderProgram(const std::string& filepath) noexcept
	{
		return std::shared_ptr<ShaderProgram>(new ShaderProgram("", ""));
	}

	std::shared_ptr<ShaderProgram> GraphicsLibrary::CreateShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) noexcept
	{
		return std::shared_ptr<ShaderProgram>(new ShaderProgram(vertexShaderCode, fragmentShaderCode));
	}

	std::shared_ptr<Texture> GraphicsLibrary::CreateTexture(const unsigned int width, const unsigned int height) noexcept
	{
		return std::shared_ptr<Texture>(new Texture(width, height));
	}

	std::shared_ptr<Texture> GraphicsLibrary::CreateTexture(const std::string& pathToTexture) noexcept
	{
		return std::shared_ptr<Texture>(new Texture(pathToTexture));
	}

	std::shared_ptr<FrameBuffer> GraphicsLibrary::CreateFrameBuffer(const FrameBufferData& data) noexcept
	{
		return std::shared_ptr<FrameBuffer>(new FrameBuffer(data));
	}

	std::shared_ptr<IndexStaticBuffer> GraphicsLibrary::CreateIndexStaticBuffer(unsigned int* indices, unsigned int count) noexcept
	{
		return std::shared_ptr<IndexStaticBuffer>(new IndexStaticBuffer(indices, count));
	}

	std::shared_ptr<VertexArrayBuffer> GraphicsLibrary::CreateVertexArrayBuffer() noexcept
	{
		return std::shared_ptr<VertexArrayBuffer>(new VertexArrayBuffer());
	}

	std::shared_ptr<VertexDynamicBuffer> GraphicsLibrary::CreateVertexDynamicBuffer(unsigned int size) noexcept
	{
		return std::shared_ptr<VertexDynamicBuffer>(new VertexDynamicBuffer(size));
	}

	std::shared_ptr<VertexStaticBuffer> GraphicsLibrary::CreateVertexStaticBuffer(float* vertices, unsigned int size) noexcept
	{
		return std::shared_ptr<VertexStaticBuffer>(new VertexStaticBuffer(vertices, size));
	}

	std::shared_ptr<Spritesheet> GraphicsLibrary::CreateSpritesheet(const std::shared_ptr<Texture>& texture, const Math::Vector2& size) noexcept
	{
		return std::shared_ptr<Spritesheet>(new Spritesheet(texture, size));
	}

}