#pragma once

#include <queue>
#include <bitset>
#include <optional>

#include "MouseEvent.h"

namespace EventsSystem
{

	class Mouse
	{

	private:
		static constexpr unsigned int bufferSize = 16u;
		
		bool leftKeyIsPressed;
		bool rightKeyIsPressed;

		float positionX;
		float positionY;

		std::queue<MouseEvent> buffer;

	public:
		bool LeftKeyIsPressed() const noexcept;
		bool RightKeyIsPressed() const noexcept;
		bool BufferIsEmpty() const noexcept;

		void Flush() noexcept;

		void OnMouseMove(float positionX, float positionY) noexcept;
		void OnLeftKeyPressed(float positionX, float positionY) noexcept;
		void OnLeftKeyReleased(float positionX, float positionY) noexcept;
		void OnRightKeyPressed(float positionX, float positionY) noexcept;
		void OnRightKeyReleased(float positionX, float positionY) noexcept;

		std::optional<MouseEvent> Read() noexcept;

	private:
		template<typename T>
		static void TrimBuffer(std::queue<T>& buffer) noexcept;
	};

}