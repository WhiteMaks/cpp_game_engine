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
		Renderer::EndScene();

		context->EndFrame();
	}

	void GraphicsEngine::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction graphics engine has started");
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