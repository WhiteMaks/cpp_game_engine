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

	void GraphicsEngine::BeginUpdate() noexcept
	{
	}

	void GraphicsEngine::EndUpdate() noexcept
	{
		window->Update();
	}

	void GraphicsEngine::BeginRender() noexcept
	{
		context->BeginFrame();
	}

	void GraphicsEngine::EndRender() noexcept
	{
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