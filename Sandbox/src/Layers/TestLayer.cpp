#include "Layers/TestLayer.h"

TestLayer::TestLayer() noexcept
	: Layer("Test layer")
{
}

void TestLayer::Init() noexcept
{
	GraphicsEngine::Renderer2D::Init();
	CreateCameraController();
	CreateTextures();
}

void TestLayer::MouseEvent(EventsSystem::MouseEvent& event) noexcept
{
	cameraController->MouseEvent(event);
}

void TestLayer::KeyboardEvent(EventsSystem::KeyboardEvent& event) noexcept
{
	cameraController->KeyboardEvent(event);
}

void TestLayer::WindowEvent(EventsSystem::WindowEvent& event) noexcept
{
	cameraController->WindowEvent(event);
}

void TestLayer::Update() noexcept
{
	cameraController->Update();
}

void TestLayer::Render() noexcept
{
	GraphicsEngine::Renderer::Clear();
	GraphicsEngine::Renderer::SetClearColor(Math::Vector4(0.2f, 0.2f, 0.2f, 1.0f));

	GraphicsEngine::Renderer2D::BeginScene(cameraController->GetCamera());
	GraphicsEngine::Renderer2D::DrawQuad(Math::Vector2(-1.0f, 0.0f), Math::Vector2(0.5f, 0.5f), Math::Vector4(1.0f, 0.0f, 1.0f, 1.0f));
	GraphicsEngine::Renderer2D::DrawQuad(Math::Vector2(1.0f, 0.0f), Math::Vector2(0.5f, 0.5f), Math::Vector4(0.0f, 0.0f, 1.0f, 1.0f));
	//GraphicsEngine::Renderer2D::DrawQuad(Math::Vector3(0.0f, 0.0f, -0.1f), Math::Vector3(0.0f, 0.0f, 45.0f), Math::Vector2(0.5f, 0.5f), texture);
	//GraphicsEngine::Renderer2D::DrawQuad(Math::Vector2(0.0f, 0.0f), Math::Vector2(0.5f, 0.5f), texture2);
	GraphicsEngine::Renderer2D::EndScene();

	//APPLICATION_DEBUG("FPS: {0}", 1.0 / GameEngine::Time::GetDeltaTime());
}

void TestLayer::Destroy() noexcept
{
	cameraController->Destroy();
	GraphicsEngine::Renderer2D::Destroy();
}

void TestLayer::CreateCameraController() noexcept
{
	cameraController = std::shared_ptr<GameEngine::OrthographicCameraController>(
		new GameEngine::OrthographicCameraController(0.0f)
	);
	cameraController->Init();
}

void TestLayer::CreateTextures() noexcept
{
	texture = std::shared_ptr<GraphicsEngine::Texture>(
		GraphicsEngine::TextureFactory::Create("assets/textures/checkerboard.png")
	);
	texture->Init();

	texture2 = std::shared_ptr<GraphicsEngine::Texture>(
		GraphicsEngine::TextureFactory::Create("assets/textures/butterfly.png")
	);
	texture2->Init();
}
