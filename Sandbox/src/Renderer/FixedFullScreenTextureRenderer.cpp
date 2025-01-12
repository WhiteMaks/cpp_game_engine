#include "Renderer/FixedFullScreenTextureRenderer.h"

struct Data
{
	std::shared_ptr<GraphicsEngine::ShaderProgram> shaderProgram;
	std::shared_ptr<GraphicsEngine::VertexStaticBuffer> vertexStaticBuffer;
	std::shared_ptr<GraphicsEngine::VertexArrayBuffer> vertexArrayBuffer;
};

static Data data;

void FixedFullScreenTextureRenderer::Init() noexcept
{
	InitBuffers();
	InitAssets();
}

void FixedFullScreenTextureRenderer::Destroy() noexcept
{
	data.vertexStaticBuffer->Destroy();
	data.vertexArrayBuffer->Destroy();
	data.shaderProgram->Destroy();
}

void FixedFullScreenTextureRenderer::Draw(const std::shared_ptr<GraphicsEngine::Texture>& texture) noexcept
{
	data.shaderProgram->Bind();
	texture->Bind();

	data.vertexArrayBuffer->Bind();
	GraphicsEngine::Renderer::DrawTriangles(data.vertexArrayBuffer);
	data.vertexArrayBuffer->Unbind();

	texture->Unbind();
	data.shaderProgram->Unbind();
}

void FixedFullScreenTextureRenderer::InitBuffers() noexcept
{
	data.vertexArrayBuffer = GraphicsEngine::GraphicsEngine::GetLibrary()->CreateVertexArrayBuffer();
	data.vertexArrayBuffer->Init();

	float vertices[4 * 5] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f
	};

	data.vertexStaticBuffer = GraphicsEngine::GraphicsEngine::GetLibrary()->CreateVertexStaticBuffer(vertices, sizeof(vertices));

	std::vector<GraphicsEngine::BufferElement> bufferElements = {
		{GraphicsEngine::BufferElementType::FLOAT_3, "a_Position"},
		{GraphicsEngine::BufferElementType::FLOAT_2, "a_TextureCoordinate"},
	};

	GraphicsEngine::BufferLayout bufferLayout(bufferElements);
	bufferLayout.Init();

	data.vertexStaticBuffer->SetLayout(bufferLayout);
	data.vertexStaticBuffer->Init();

	data.vertexArrayBuffer->AddVertexBuffer(data.vertexStaticBuffer);

	unsigned int indices[6] = {
		0, 1, 2, 2, 3, 0
	};

	std::shared_ptr<GraphicsEngine::IndexStaticBuffer> indexBuffer = GraphicsEngine::GraphicsEngine::GetLibrary()->CreateIndexStaticBuffer(indices, sizeof(indices) / sizeof(unsigned int));
	indexBuffer->Init();

	data.vertexArrayBuffer->SetIndexBuffer(indexBuffer);
}

void FixedFullScreenTextureRenderer::InitAssets() noexcept
{
	data.shaderProgram = GraphicsEngine::GraphicsEngine::GetLibrary()->CreateShaderProgram("assets/shaders/fixed_full_screen_texture_shader");
	data.shaderProgram->Init();
	data.shaderProgram->Bind();
	data.shaderProgram->SetUniformInt("u_Texture", 0);
}
