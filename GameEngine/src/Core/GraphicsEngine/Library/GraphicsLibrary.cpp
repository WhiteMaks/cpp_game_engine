#include "Core/GraphicsEngine/Library/GraphicsLibrary.h"

namespace GraphicsEngine
{

	std::shared_ptr<GraphicsContext> GraphicsLibrary::CreateContext() noexcept
	{
		return std::shared_ptr<GraphicsContext>(new GraphicsContext());
	}

	std::shared_ptr<Renderer> GraphicsLibrary::CreateRenderer() noexcept
	{
		return std::shared_ptr<Renderer>(new Renderer());
	}

	std::shared_ptr<ShaderProgram> GraphicsLibrary::CreateShaderProgram() noexcept
	{
		return std::shared_ptr<ShaderProgram>(new ShaderProgram());
	}

	std::shared_ptr<Texture> GraphicsLibrary::CreateTexture() noexcept
	{
		return std::shared_ptr<Texture>(new Texture());
	}

	std::shared_ptr<FrameBuffer> GraphicsLibrary::CreateFrameBuffer() noexcept
	{
		return std::shared_ptr<FrameBuffer>(new FrameBuffer());
	}

	std::shared_ptr<IndexStaticBuffer> GraphicsLibrary::CreateIndexStaticBuffer() noexcept
	{
		return std::shared_ptr<IndexStaticBuffer>(new IndexStaticBuffer());
	}

	std::shared_ptr<VertexArrayBuffer> GraphicsLibrary::CreateVertexArrayBuffer() noexcept
	{
		return std::shared_ptr<VertexArrayBuffer>(new VertexArrayBuffer());
	}

	std::shared_ptr<VertexDynamicBuffer> GraphicsLibrary::CreateVertexDynamicBuffer() noexcept
	{
		return std::shared_ptr<VertexDynamicBuffer>(new VertexDynamicBuffer());
	}

	std::shared_ptr<VertexStaticBuffer> GraphicsLibrary::CreateVertexStaticBuffer() noexcept
	{
		return std::shared_ptr<VertexStaticBuffer>(new VertexStaticBuffer());
	}

}