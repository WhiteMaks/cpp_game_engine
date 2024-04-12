#include "BrowserWindow.h" 
#include "ExitCodes.h"

namespace Platform
{

	SDL_Window* BrowserWindow::window;

	BrowserWindow::BrowserWindow(const GraphicsEngine::WindowData& windowData) noexcept
		: Window(windowData)
	{
	}

	void BrowserWindow::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization browser window [{0} ({1}, {2})] has started", windowData.Title, windowData.Width, windowData.Height);

		GRAPHICS_ENGINE_DEBUG("Initialization SDL has started");
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			GRAPHICS_ENGINE_CRITICAL("SDL not initialized! Error: {0}", SDL_GetError());
			exit(GameEngine::WINDOW_INITIALIZAATION_FAILED);
		}
		GRAPHICS_ENGINE_DEBUG("Initialization SDL completed");

		GRAPHICS_ENGINE_DEBUG("Initialization SDL window has started");
		window = SDL_CreateWindow(
			windowData.Title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			windowData.Width, windowData.Height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
		);

		if (!window)
		{
			GRAPHICS_ENGINE_CRITICAL("SDL window not initialized!");
			SDL_Quit();
			exit(GameEngine::WINDOW_INITIALIZAATION_FAILED);
		}
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
		GRAPHICS_ENGINE_DEBUG("Initialization SDL window completed");

		shouldClose = false;

		GRAPHICS_ENGINE_INFO("Initialization browser window completed");
	}

	void BrowserWindow::Update() noexcept
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type)
		{

		case SDL_QUIT:
			EventsSystem::EventManager::GetInstance()->GetWindow()->OnClose();
			break;

		case SDL_MOUSEMOTION:
			EventsSystem::EventManager::GetInstance()->GetMouse()->OnMouseMove((float) event.motion.x, (float) event.motion.y);
			break;

		case SDL_KEYDOWN:
			EventsSystem::EventManager::GetInstance()->GetKetboard()->OnKeyPressed(event.key.keysym.sym);
			break;

		case SDL_KEYUP:
			EventsSystem::EventManager::GetInstance()->GetKetboard()->OnKeyReleased(event.key.keysym.sym);
			break;

		case SDL_WINDOWEVENT:
			SDL_WindowEvent windowEvent = event.window;
			if (windowEvent.event == SDL_WINDOWEVENT_RESIZED || windowEvent.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				EventsSystem::EventManager::GetInstance()->GetWindow()->OnResize(windowEvent.data1, windowEvent.data2);
			}
			break;
		}
	}

	void BrowserWindow::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction browser window has started");

		SDL_DestroyWindow(window);
		GRAPHICS_ENGINE_TRACE("SDL window destroyed");
		SDL_Quit();
		GRAPHICS_ENGINE_TRACE("SDL terminated");

		GRAPHICS_ENGINE_INFO("Destruction browser window completed");
	}

}