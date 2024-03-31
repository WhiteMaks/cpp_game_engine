#include "WindowsWindow.h"

namespace Platform
{
	HWND WindowsWindow::window;

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	WindowsWindow::WindowsWindow(const GraphicsEngine::WindowData& windowData) noexcept
		: Window(windowData), hInstance(nullptr)
	{
	}

	WindowsWindow::~WindowsWindow() noexcept
	{
	}

	void WindowsWindow::Init() noexcept
	{
		GRAPHICS_ENGINE_INFO("Initialization windows window [{0}] has started", windowData.Title);
		
		const char className[] = "Windows window";

		hInstance = GetModuleHandle(NULL);

		GRAPHICS_ENGINE_DEBUG("Initialization WNDCLASS has started");
		WNDCLASS wc = {};
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = hInstance;
		wc.lpszClassName = className;
		RegisterClass(&wc);
		GRAPHICS_ENGINE_DEBUG("Initialization WNDCLASS completed");

		GRAPHICS_ENGINE_DEBUG("Initialization HWND window has started");
		window = CreateWindowEx(
			0,
			className,
			windowData.Title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 
			CW_USEDEFAULT,
			windowData.Width, 
			windowData.Height,
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);

		if (!window)
		{
			GRAPHICS_ENGINE_CRITICAL("HWND window not initialized!");
			exit(GameEngine::WINDOW_INITIALIZAATION_FAILED);
		}
		GRAPHICS_ENGINE_DEBUG("Initialization HWND window completed");

		shouldClose = false;
		ShowWindow(window, SW_MAXIMIZE);

		GRAPHICS_ENGINE_INFO("Initialization windows window completed");
	}

	void WindowsWindow::Update() noexcept
	{
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void WindowsWindow::Destroy() noexcept
	{
		GRAPHICS_ENGINE_INFO("Destruction windows window has started");

		DestroyWindow(window);
		GRAPHICS_ENGINE_TRACE("HWND window destroyed");

		GRAPHICS_ENGINE_INFO("Destruction windows window completed");
	}

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{

		case WM_SETCURSOR:
		{
			if (LOWORD(lParam) == HTCLIENT)
			{
				SetCursor(LoadCursor(NULL, IDC_ARROW));
			}
			break;
		}
		case WM_CLOSE:
		{
			EventsSystem::EventManager::GetInstance()->GetWindow()->OnClose();
			return 0;
		}
		case WM_SIZE:
		{
			EventsSystem::EventManager::GetInstance()->GetWindow()->OnResize(LOWORD(lParam), HIWORD(lParam));
			return 0;
		}
		case WM_MOUSEMOVE:
		{
			EventsSystem::EventManager::GetInstance()->GetMouse()->OnMouseMove(LOWORD(lParam), HIWORD(lParam));
			return 0;
		}
		case WM_KEYDOWN:
		{
			EventsSystem::EventManager::GetInstance()->GetKetboard()->OnKeyPressed(wParam);
			return 0;
		}
		case WM_KEYUP:
		{
			EventsSystem::EventManager::GetInstance()->GetKetboard()->OnKeyReleased(wParam);
			return 0;
		}

		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

}