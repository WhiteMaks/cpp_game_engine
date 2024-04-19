#include "Core/GraphicsEngine/GraphicsEngine.h"

namespace GraphicsEngine
{

	GraphicsAPI GraphicsEngine::api = GraphicsAPI::OpenGL;

	GraphicsEngine::GraphicsEngine(const std::string& windowTitle, const unsigned int windowWidth, const unsigned int windowHeight, GraphicsAPI api)
	{
		GraphicsEngine::api = api;

		window = std::unique_ptr<Window>(
			WindowFactory::Create(
				WindowData(windowTitle, windowWidth, windowHeight)
			)
		);
	}

	void GraphicsEngine::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization graphics engine has started");
		window->Init();

		context = std::unique_ptr<GraphicsContext>(
			GraphicsContextFactory::Create()
		);
		context->Init();

		Renderer::Init();
		GRAPHICS_ENGINE_INFO("Initialization graphics engine completed");













		std::string vertex = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec4 v_Color;

			void main() {
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragment = R"(
			#version 460 core

			layout(location = 0) out vec4 color;

			in vec4 v_Color;

			void main() {
				color = v_Color;
			}
		)";

		shaderProgram = std::shared_ptr<ShaderProgram>(
			ShaderProgramFactory::Create(vertex, fragment)
		);

		shaderProgram->Init();


		vertexArrayBuffer = std::shared_ptr<VertexArrayBuffer>(
			BufferFactory::CreateVertexArrayBuffer()
		);
		vertexArrayBuffer->Init();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<VertexStaticBuffer> vertexBuffer = std::shared_ptr<VertexStaticBuffer>(
			BufferFactory::CreateVertexStaticBuffer(vertices, sizeof(vertices))
		);

		std::vector<BufferElement> bufferElements = {
			{BufferElementType::FLOAT_3, "a_Position"},
			{BufferElementType::FLOAT_4, "a_Color"},
		};

		BufferLayout bufferLayout(bufferElements);
		bufferLayout.Init();

		vertexBuffer->SetLayout(bufferLayout);
		vertexBuffer->Init();

		vertexArrayBuffer->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = {
			0, 1, 2
		};

		std::shared_ptr<IndexStaticBuffer> indexBuffer = std::shared_ptr<IndexStaticBuffer>(
			BufferFactory::CreateIndexStaticBuffer(indices, sizeof(indices) / sizeof(unsigned int))
		);
		indexBuffer->Init();

		vertexArrayBuffer->SetIndexBuffer(indexBuffer);
	}

	GraphicsAPI GraphicsEngine::GetAPI() noexcept
	{
		return api;
	}

	void GraphicsEngine::Update() noexcept
	{
		window->Update();
	}

	void GraphicsEngine::Render() noexcept
	{
		context->BeginFrame();

		Renderer::Clear();
		Renderer::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

		Renderer::BeginScene();

		shaderProgram->Bind();
		Renderer::Submit(vertexArrayBuffer);
		shaderProgram->Unbind();

		Renderer::EndScene();

		context->EndFrame();
	}

	void GraphicsEngine::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction graphics engine has started");
		vertexArrayBuffer->Destroy();
		shaderProgram->Destroy();

		Renderer::Destroy();

		context->Destroy();
		window->Destroy();
		GRAPHICS_ENGINE_INFO("Destruction graphics engine completed");
	}

	void GraphicsEngine::Stop() noexcept
	{
		window->ShouldClose(true);
		GRAPHICS_ENGINE_INFO("Stopping graphics engine...");
	}

	bool GraphicsEngine::ShouldStop() noexcept
	{
		return window->ShouldClose();
	}

}