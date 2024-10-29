#include "Scripts/CameraController.h"

void CameraController::Init() noexcept
{
	cameraComponent = &GetComponent<ECS::CameraComponent>();
	transformComponent = &GetComponent<ECS::TransformComponent>();
}

void CameraController::Update() noexcept
{
	if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyD))
	{
		transformComponent->position.x += cameraSpeed * GameEngine::Time::GetDeltaTime();
	}

	if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyA))
	{
		transformComponent->position.x -= (cameraSpeed * GameEngine::Time::GetDeltaTime());
	}

	if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyW))
	{
		transformComponent->position.y += (cameraSpeed * GameEngine::Time::GetDeltaTime());
	}

	if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyS))
	{
		transformComponent->position.y -= (cameraSpeed * GameEngine::Time::GetDeltaTime());
	}

	if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyE))
	{
		transformComponent->rotation.z = (transformComponent->rotation.z - (cameraSpeed * GameEngine::Time::GetDeltaTime() * 30));
	}

	if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyQ))
	{
		transformComponent->rotation.z = (transformComponent->rotation.z + (cameraSpeed * GameEngine::Time::GetDeltaTime() * 30));
	}
}

void CameraController::Destroy() noexcept
{
}

void CameraController::KeyboardEvent(EventsSystem::KeyboardEvent& keyboardEvent) noexcept
{
	if (keyboardEvent.GetCode() == EventsSystem::EventManager::keyR && keyboardEvent.IsPressed())
	{
		zoom--;
		zoom = std::max(zoom, 0.5f);
		cameraComponent->camera.SetProjectionMatrix(glm::ortho(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom, -1.0f, 1.0f));

		keyboardEvent.Invalidate();
	}

	if (keyboardEvent.GetCode() == EventsSystem::EventManager::keyF && keyboardEvent.IsPressed())
	{
		zoom++;
		cameraComponent->camera.SetProjectionMatrix(glm::ortho(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom, -1.0f, 1.0f));

		keyboardEvent.Invalidate();
	}
}

void CameraController::WindowEvent(EventsSystem::WindowEvent& windowEvent) noexcept
{
	if (windowEvent.GetType() == EventsSystem::WindowEventType::RESIZE)
	{
		aspectRatio = (float) windowEvent.GetWidth() / (float) windowEvent.GetHeight();
		cameraComponent->camera.SetProjectionMatrix(glm::ortho(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom, -1.0f, 1.0f));
	}
}
