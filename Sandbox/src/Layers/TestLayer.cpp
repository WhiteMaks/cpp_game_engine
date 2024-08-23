#include "Layers/TestLayer.h"
#include "Renderer/FixedFullScreenTextureRenderer.h"

TestLayer::TestLayer() noexcept
	: Layer("Test layer")
{
}

void TestLayer::Init() noexcept
{
	GraphicsEngine::Renderer2D::Init();
	FixedFullScreenTextureRenderer::Init();

	CreateFrameBuffer();
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
	frameBuffer->WindowEvent(event);
	cameraController->WindowEvent(event);
}

void TestLayer::Update() noexcept
{
	cameraController->Update();
}

void TestLayer::Render() noexcept
{
	frameBuffer->Bind();
	GraphicsEngine::Renderer::SetClearColor(Math::Vector4(0.2f, 0.2f, 0.2f, 1.0f));
	GraphicsEngine::Renderer::Clear();

	GraphicsEngine::Renderer2D::BeginScene(cameraController->GetCamera());
	GraphicsEngine::Renderer2D::DrawSprite(Math::Vector2(0.0f, 0.0f), Math::Vector2(1.0f, 1.0f), spriteTest);
	GraphicsEngine::Renderer2D::EndScene();
	frameBuffer->Unbind();

	GraphicsEngine::Renderer::Clear();
	FixedFullScreenTextureRenderer::Draw(frameBuffer->GetColorAttachment());

	//APPLICATION_DEBUG("FPS: {0}", 1.0 / GameEngine::Time::GetDeltaTime());
}

void TestLayer::Destroy() noexcept
{
	frameBuffer->Destroy();
	cameraController->Destroy();
	GraphicsEngine::Renderer2D::Destroy();
	FixedFullScreenTextureRenderer::Destroy();
}

void TestLayer::CreateFrameBuffer() noexcept
{
	frameBuffer = GraphicsEngine::BufferFactory::CreateFrameBuffer(GraphicsEngine::FrameBufferData(1280, 720));
	frameBuffer->Init();
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
	std::shared_ptr<GraphicsEngine::Texture> spritesheetTinyTownTexture = GraphicsEngine::TextureFactory::Create("assets/spritesheets/tiny_town_16x16_0x0.png");
	spritesheetTinyTownTexture->Init();

	spritesheetTinyTown = std::shared_ptr<GraphicsEngine::Spritesheet>(
		new GraphicsEngine::Spritesheet(spritesheetTinyTownTexture, Math::Vector2(16.0f, 16.0f))
	);

	spriteTest = spritesheetTinyTown->GetSprite(Math::Vector2(9.0f, 6.0f));
}
