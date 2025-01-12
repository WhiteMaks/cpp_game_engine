#include <GameEngine.h>

class Rotation : public ECS::ScriptableEntity
{
private:
	ECS::TransformComponent* transformComponent;

public:
	Rotation() noexcept;

public:
	void Init() noexcept override;
	void Update() noexcept override;
	void Destroy() noexcept override;

	void KeyboardEvent(EventsSystem::KeyboardEvent& keyboardEvent) noexcept override;
	void WindowEvent(EventsSystem::WindowEvent& windowEvent) noexcept override;
};