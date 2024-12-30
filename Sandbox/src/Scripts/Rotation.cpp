#include "Scripts/Rotation.h"

void Rotation::Init() noexcept
{
	transformComponent = &GetComponent<ECS::TransformComponent>();
	APPLICATION_INFO("Init rotation script");
}

void Rotation::Update() noexcept
{
	transformComponent->rotation.z += 25 * GameEngine::Time::GetDeltaTime();
}

void Rotation::Destroy() noexcept
{
	APPLICATION_INFO("Destroy rotation script");
}

void Rotation::KeyboardEvent(EventsSystem::KeyboardEvent& keyboardEvent) noexcept
{

}

void Rotation::WindowEvent(EventsSystem::WindowEvent& windowEvent) noexcept
{
	
}
