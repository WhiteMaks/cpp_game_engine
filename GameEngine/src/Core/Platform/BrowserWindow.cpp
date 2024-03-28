#include "BrowserWindow.h" 
#include "ExitCodes.h"

namespace Platform
{

	BrowserWindow::BrowserWindow(const GraphicsEngine::WindowData& windowData) noexcept
		: Window(windowData), window(nullptr)
	{
	}

	BrowserWindow::~BrowserWindow() noexcept
	{
	}

	void BrowserWindow::Init() noexcept
	{
		WINDOW_INFO("Initialization browser window [{0} ({1}, {2})] has started", windowData.Title, windowData.Width, windowData.Height);

		WINDOW_DEBUG("Initialization SDL has started");
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			WINDOW_CRITICAL("SDL not initialized! Error: {0}", SDL_GetError());
			exit(GameEngine::WINDOW_INITIALIZAATION_FAILED);
		}
		WINDOW_DEBUG("Initialization SDL completed");

		WINDOW_DEBUG("Initialization SDL window has started");
		window = SDL_CreateWindow(
			windowData.Title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			windowData.Width, windowData.Height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
		);

		if (!window)
		{
			WINDOW_CRITICAL("SDL window not initialized!");
			SDL_Quit();
			exit(GameEngine::WINDOW_INITIALIZAATION_FAILED);
		}
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
		SDL_GL_CreateContext(window);
		WINDOW_DEBUG("Initialization SDL window completed");

		shouldClose = false;

		WINDOW_DEBUG("Initialization SDL events has started");
		WINDOW_DEBUG("Initialization SDL events completed");

		WINDOW_INFO("Initialization browser window completed");
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

		SDL_GL_SwapWindow(window);
	}

	void BrowserWindow::Destroy() noexcept
	{
		WINDOW_INFO("Destruction browser window has started");

		SDL_DestroyWindow(window);
		WINDOW_TRACE("SDL window destroyed");
		SDL_Quit();
		WINDOW_TRACE("SDL terminated");

		WINDOW_INFO("Destruction browser window completed");
	}

}