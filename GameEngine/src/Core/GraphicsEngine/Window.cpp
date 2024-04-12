#include "Core/GraphicsEngine/Window.h"

namespace GraphicsEngine
{

	WindowData::WindowData(const std::string& title, unsigned int width, unsigned int height) noexcept
		: Title(title), Width(width), Height(height)
	{
	}

	Window::Window(const WindowData& windowData) noexcept
		: windowData(windowData)
	{
	}

	void Window::Init() noexcept
	{
	}

	void Window::Update() noexcept
	{
	}

	void Window::Destroy() noexcept
	{
	}

	unsigned int Window::GetWidth() const noexcept
	{
		return windowData.Width;
	}

	unsigned int Window::GetHeight() const noexcept
	{
		return windowData.Height;
	}

	bool Window::ShouldClose() const noexcept
	{
		return shouldClose;
	}

	void Window::ShouldClose(bool shouldClose) noexcept
	{
		this->shouldClose = shouldClose;
	}

}
