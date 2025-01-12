#pragma once 

#include "Core/GraphicsEngine/Library/GraphicsLibrary.h"

namespace GraphicsEngine
{

	class WebGLGraphicsLibrary : public GraphicsLibrary
	{
	public:
		std::shared_ptr<GraphicsContext> CreateContext() noexcept override;
		std::shared_ptr<RendererAPI> CreateRenderer() noexcept override;
		std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& filepath) noexcept override;
		std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) noexcept override;
		std::shared_ptr<Texture> CreateTexture(const unsigned int width, const unsigned int height) noexcept override;
		std::shared_ptr<Texture> CreateTexture(const std::string& pathToTexture) noexcept override;
		std::shared_ptr<FrameBuffer> CreateFrameBuffer(const FrameBufferData& data) noexcept override;
		std::shared_ptr<IndexStaticBuffer> CreateIndexStaticBuffer(unsigned int* indices, unsigned int count) noexcept override;
		std::shared_ptr<VertexArrayBuffer> CreateVertexArrayBuffer() noexcept override;
		std::shared_ptr<VertexDynamicBuffer> CreateVertexDynamicBuffer(unsigned int size) noexcept override;
		std::shared_ptr<VertexStaticBuffer> CreateVertexStaticBuffer(float* vertices, unsigned int size) noexcept override;
	};

}