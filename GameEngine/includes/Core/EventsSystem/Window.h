#pragma once

#include <queue>
#include <optional>

#include "WindowEvent.h"

namespace EventsSystem
{

	class Window
	{

	private:
		static constexpr unsigned int bufferSize = 16u;

		std::queue<WindowEvent> buffer;

	public:
		void Flush() noexcept;

		void OnClose() noexcept;
		void OnResize(unsigned int width, unsigned int height) noexcept;

		bool BufferIsEmpty() const noexcept;

		std::optional<WindowEvent> Read() noexcept;

	private:
		template<typename T>
		static void TrimBuffer(std::queue<T>& buffer) noexcept;
	};

}