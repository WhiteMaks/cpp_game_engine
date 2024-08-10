#pragma once

#include <GameEngine.h>

class TestLayer : public GameEngine::Layer
{

private:
	std::shared_ptr<GraphicsEngine::ShaderProgram> shaderProgram;
	std::shared_ptr<GraphicsEngine::VertexArrayBuffer> vertexArrayBuffer;
	std::shared_ptr<GraphicsEngine::Texture> texture;
	std::shared_ptr<GraphicsEngine::Texture> texture2;

	std::shared_ptr<GameEngine::OrthographicCameraController> cameraController;

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
};