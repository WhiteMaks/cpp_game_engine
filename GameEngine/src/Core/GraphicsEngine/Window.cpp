#include "Core/GraphicsEngine/Window.h"

namespace GameEngine
{

	WindowData::WindowData(const std::string& title, unsigned int width, unsigned int height) noexcept
		: Title(title), Width(width), Height(height)
	{
	}

	Window::Window(const WindowData& windowData)
		: windowData(windowData)
	{
	}

	Window::~Window()
	{
	}

	void Window::Init()
	{
	}

	void Window::Update()
	{
	}

	void Window::Destroy()
	{
	}

	unsigned int Window::GetWidth() const
	{
		return windowData.Width;
	}

	unsigned int Window::GetHeight() const
	{
		return windowData.Height;
	}

}