#include "Layers/TestLayer.h"

#include "Renderer/FixedFullScreenTextureRenderer.h"
#include "Scripts/CameraController.h"
#include "Scripts/Rotation.h"

TestLayer::TestLayer() noexcept
	: Layer("Test layer")
{
}

void TestLayer::Init() noexcept
{
	GraphicsEngine::Renderer2D::Init();
	FixedFullScreenTextureRenderer::Init();

	CreateFrameBuffer();
	CreateTextures();
	CreateScene();
}

void TestLayer::MouseEvent(EventsSystem::MouseEvent& event) noexcept
{
	scene->MouseEvent(event);
}

void TestLayer::KeyboardEvent(EventsSystem::KeyboardEvent& event) noexcept
{
	scene->KeyboardEvent(event);
}

void TestLayer::WindowEvent(EventsSystem::WindowEvent& event) noexcept
{
	frameBuffer->WindowEvent(event);
	scene->WindowEvent(event);
}

void TestLayer::Update() noexcept
{
	scene->Update();
}

void TestLayer::Render() noexcept
{
	RenderInFrameBuffer();
	RenderInWindow();

	//APPLICATION_DEBUG("FPS: {0}", 1.0 / GameEngine::Time::GetDeltaTime());
}

void TestLayer::Destroy() noexcept
{
	scene->Destroy();
	frameBuffer->Destroy();
	GraphicsEngine::Renderer2D::Destroy();
	FixedFullScreenTextureRenderer::Destroy();
}

void TestLayer::CreateFrameBuffer() noexcept
{
	frameBuffer = GraphicsEngine::BufferFactory::CreateFrameBuffer(GraphicsEngine::FrameBufferData(1280, 720));
	frameBuffer->Init();
}

void TestLayer::CreateTextures() noexcept
{
	std::shared_ptr<GraphicsEngine::Texture> spritesheetTinyTownTexture = GraphicsEngine::TextureFactory::Create("assets/spritesheets/tiny_town_16x16_0x0.png");
	spritesheetTinyTownTexture->Init();

	spritesheetTinyTown = std::shared_ptr<GraphicsEngine::Spritesheet>(
		new GraphicsEngine::Spritesheet(spritesheetTinyTownTexture, Math::Vector2(16.0f, 16.0f))
	);
}

void TestLayer::CreateScene() noexcept
{
	scene = std::shared_ptr<ECS::Scene>(new ECS::Scene());
	scene->Init();

	ECS::Entity cameraEntity = scene->CreateEntity("Camera");
	ECS::CameraComponent& cameraComponent = cameraEntity.AddComponent<ECS::CameraComponent>();
	cameraEntity.AddComponent<ECS::CppScriptComponent>().Bind<CameraController>();

	ECS::Entity entity = scene->CreateEntity("test");
	entity.AddComponent<ECS::QuadComponent>();
	entity.AddComponent<ECS::CppScriptComponent>().Bind<Rotation>();

	ECS::SpriteComponent& spriteComponent = entity.AddComponent<ECS::SpriteComponent>();
	spriteComponent.sprite = spritesheetTinyTown->GetSprite(Math::Vector2(9.0f, 6.0f));
}

void TestLayer::RenderInFrameBuffer() noexcept
{
	frameBuffer->Bind();
	GraphicsEngine::Renderer::SetClearColor(Math::Vector4(0.2f, 0.2f, 0.2f, 1.0f));
	GraphicsEngine::Renderer::Clear();
	scene->Render();
	frameBuffer->Unbind();
}

void TestLayer::RenderInWindow() noexcept
{
	GraphicsEngine::Renderer::Clear();
	FixedFullScreenTextureRenderer::Draw(frameBuffer->GetColorAttachment());
}
