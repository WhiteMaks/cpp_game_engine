#pragma once

#include "Core/GraphicsEngine/Renderer/OrthographicCamera.h"
#include "Core/EventsSystem/EventManager.h"

namespace GraphicsEngine
{
	class GAME_ENGINE_API OrthographicCameraController
	{
	private:
		float cameraSpeed;
		float aspectRatio;
		float zoom;

		OrthographicCamera camera;

	public:
		OrthographicCameraController(float aspectRatio);

	public:
		void Init() noexcept;
		void MouseEvent(EventsSystem::MouseEvent& mouseEvent) noexcept;
		void KeyboardEvent(EventsSystem::KeyboardEvent& keyboardEvent) noexcept;
		void WindowEvent(EventsSystem::WindowEvent& windowEvent) noexcept;
		void Update() noexcept;
		void Destroy() noexcept;

		OrthographicCamera& GetCamera() noexcept;
	};
}