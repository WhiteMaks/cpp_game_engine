#include "EventsSystem/Window.h"

namespace EventsSystem
{

	void Window::Flush() noexcept
	{
		buffer = std::queue<WindowEvent>();
	}

	void Window::OnClose() noexcept
	{
		buffer.push(WindowEvent(WindowEventType::CLOSE, 0, 0));
		TrimBuffer(buffer);
	}

	void Window::OnResize(unsigned int width, unsigned int height) noexcept
	{
		buffer.push(WindowEvent(WindowEventType::RESIZE, width, height));
		TrimBuffer(buffer);
	}

	bool Window::BufferIsEmpty() const noexcept
	{
		return buffer.empty();
	}

	std::optional<WindowEvent> Window::Read() noexcept
	{
		if (buffer.size() > 0u)
		{
			WindowEvent windowEvent = buffer.front();
			buffer.pop();
			return windowEvent;
		}

		return {};
	}

	template<typename T>
	inline void Window::TrimBuffer(std::queue<T>& buffer) noexcept
	{
		while (buffer.size() > bufferSize)
		{
			buffer.pop();
		}
	}

}