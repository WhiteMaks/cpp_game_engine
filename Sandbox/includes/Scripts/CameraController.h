#include <GameEngine.h>

class CameraController : public ECS::ScriptableEntity
{
private:
	float cameraSpeed = 0.5f;
	float aspectRatio = 0.0f;
	float zoom = 1.0f;

	ECS::CameraComponent* cameraComponent;
	ECS::TransformComponent* transformComponent;

public:
	void Init() noexcept override;
	void Update() noexcept override;
	void Destroy() noexcept override;

	void KeyboardEvent(EventsSystem::KeyboardEvent& keyboardEvent) noexcept override;
	void WindowEvent(EventsSystem::WindowEvent& windowEvent) noexcept override;
};