#include "Core/GraphicsEngine/GraphicsEngine.h"

#include "Core/GraphicsEngine/Library/GraphicsLibraryFactory.h"
#include "Core/GraphicsEngine/Library/Renderer.h"

namespace GraphicsEngine
{

	GraphicsAPI GraphicsEngine::api = GraphicsAPI::OpenGL;
	std::shared_ptr<GraphicsLibrary> GraphicsEngine::library = nullptr;

	GraphicsEngine::GraphicsEngine(const std::string& windowTitle, const unsigned int windowWidth, const unsigned int windowHeight, GraphicsAPI api)
	{
		GraphicsEngine::api = api;

		window = WindowFactory::Create(
			WindowData(windowTitle, windowWidth, windowHeight)
		);

		library = GraphicsLibraryFactory::Create();
	}

	void GraphicsEngine::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization graphics engine has started");
		window->Init();

		context = library->CreateContext();
		context->Init();

		Renderer::Init();
		GRAPHICS_ENGINE_INFO("Initialization graphics engine completed");
	}

	GraphicsAPI GraphicsEngine::GetAPI() noexcept
	{
		return api;
	}

	std::shared_ptr<GraphicsLibrary> GraphicsEngine::GetLibrary() noexcept
	{
		return library;
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

	void GraphicsEngine::Resize(const unsigned int width, const unsigned int height) noexcept
	{
		Renderer::Resize(width, height);
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