#pragma once

#include <GameEngine.h>

class TestLayer : public GameEngine::Layer
{

private:
	std::shared_ptr<GraphicsEngine::FrameBuffer> frameBuffer;

	std::shared_ptr<GraphicsEngine::Spritesheet> spritesheetCharacter;

	std::shared_ptr<ECS::Scene> scene;

public:
	TestLayer() noexcept;

public:
	void Init() noexcept override;
	void MouseEvent(EventsSystem::MouseEvent& event) noexcept override;
	void KeyboardEvent(EventsSystem::KeyboardEvent& event) noexcept override;
	void WindowEvent(EventsSystem::WindowEvent& event) noexcept override;
	void Update() noexcept override;
	void Render() noexcept override;
	void Destroy() noexcept override;

private:
	void CreateFrameBuffer() noexcept;
	void CreateTextures() noexcept;
	void CreateScene() noexcept;

	void RenderInFrameBuffer() noexcept;
	void RenderInWindow() noexcept;
};