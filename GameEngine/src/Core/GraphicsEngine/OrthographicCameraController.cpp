#include "Core/GraphicsEngine/OrthographicCameraController.h"
#include "Tools/Time.h"

namespace GraphicsEngine
{

	OrthographicCameraController::OrthographicCameraController(float aspectRatio)
		: aspectRatio(aspectRatio), zoom(1.0f), cameraSpeed(0.5f), camera(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom)
	{
	}

	void OrthographicCameraController::Init() noexcept
	{
		camera.SetPosition({0.0f, 0.0f, 0.0f});
		camera.SetRotation(0.0f);
	}

	void OrthographicCameraController::MouseEvent(EventsSystem::MouseEvent& mouseEvent) noexcept
	{
	}

	void OrthographicCameraController::KeyboardEvent(EventsSystem::KeyboardEvent& keyboardEvent) noexcept
	{
		if (keyboardEvent.GetCode() == EventsSystem::EventManager::keyR && keyboardEvent.IsPressed())
		{
			zoom--;
			zoom = std::max(zoom, 1.0f);
			camera.RecalculateProjectionMatrix(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);

			keyboardEvent.Invalidate();
		}

		if (keyboardEvent.GetCode() == EventsSystem::EventManager::keyF && keyboardEvent.IsPressed())
		{
			zoom++;
			camera.RecalculateProjectionMatrix(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);

			keyboardEvent.Invalidate();
		}
	}

	void OrthographicCameraController::WindowEvent(EventsSystem::WindowEvent& windowEvent) noexcept
	{
		if (windowEvent.GetType() == EventsSystem::WindowEventType::RESIZE)
		{
			aspectRatio = (float) windowEvent.GetWidth() / (float) windowEvent.GetHeight();
			camera.RecalculateProjectionMatrix(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);
		}
	}

	void OrthographicCameraController::Update() noexcept
	{
		if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyD))
		{
			camera.GetPosition().x += cameraSpeed * GameEngine::Time::GetDeltaTime();
		}

		if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyA))
		{
			camera.GetPosition().x -= (cameraSpeed * GameEngine::Time::GetDeltaTime());
		}

		if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyW))
		{
			camera.GetPosition().y += (cameraSpeed * GameEngine::Time::GetDeltaTime());
		}

		if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyS))
		{
			camera.GetPosition().y -= (cameraSpeed * GameEngine::Time::GetDeltaTime());
		}

		if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyE))
		{
			camera.SetRotation(camera.GetRotation() - (cameraSpeed * GameEngine::Time::GetDeltaTime() * 30));
		}

		if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyQ))
		{
			camera.SetRotation(camera.GetRotation() + (cameraSpeed * GameEngine::Time::GetDeltaTime() * 30));
		}

		camera.Update();
	}

	void OrthographicCameraController::Destroy() noexcept
	{
		
	}

	OrthographicCamera& OrthographicCameraController::GetCamera() noexcept
	{
		return camera;
	}

}