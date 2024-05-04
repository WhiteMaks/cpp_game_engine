#include "WindowsWindow.h"

namespace Platform
{
	HWND WindowsWindow::window;

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	WindowsWindow::WindowsWindow(const GraphicsEngine::WindowData& windowData) noexcept
		: Window(windowData), hInstance(nullptr)
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

		EventsSystem::EventManager::keyA = 65;
		EventsSystem::EventManager::keyB = 66;
		EventsSystem::EventManager::keyC = 67;
		EventsSystem::EventManager::keyD = 68;
		EventsSystem::EventManager::keyE = 69;
		EventsSystem::EventManager::keyF = 70;
		EventsSystem::EventManager::keyG = 71;
		EventsSystem::EventManager::keyH = 72;
		EventsSystem::EventManager::keyI = 73;
		EventsSystem::EventManager::keyJ = 74;
		EventsSystem::EventManager::keyK = 75;
		EventsSystem::EventManager::keyL = 76;
		EventsSystem::EventManager::keyM = 77;
		EventsSystem::EventManager::keyN = 78;
		EventsSystem::EventManager::keyO = 79;
		EventsSystem::EventManager::keyP = 80;
		EventsSystem::EventManager::keyQ = 81;
		EventsSystem::EventManager::keyR = 82;
		EventsSystem::EventManager::keyS = 83;
		EventsSystem::EventManager::keyT = 84;
		EventsSystem::EventManager::keyU = 85;
		EventsSystem::EventManager::keyV = 86;
		EventsSystem::EventManager::keyW = 87;
		EventsSystem::EventManager::keyX = 88;
		EventsSystem::EventManager::keyY = 89;
		EventsSystem::EventManager::keyZ = 90;

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