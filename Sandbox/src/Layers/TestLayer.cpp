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
	scene->SaveInYaml("data/scenes/");
	scene->Destroy();
	frameBuffer->Destroy();
	GraphicsEngine::Renderer2D::Destroy();
	FixedFullScreenTextureRenderer::Destroy();
}

void TestLayer::CreateFrameBuffer() noexcept
{
	frameBuffer = GraphicsEngine::GraphicsEngine::GetLibrary()->CreateFrameBuffer(GraphicsEngine::FrameBufferData(1280, 720));
	frameBuffer->Init();
}

void TestLayer::CreateTextures() noexcept
{
	std::shared_ptr<GraphicsEngine::Texture> spritesheetCharacterTexture = GraphicsEngine::GraphicsEngine::GetLibrary()->CreateTexture("assets/spritesheets/character_spritesheet.png");
	spritesheetCharacterTexture->Init();

	spritesheetCharacter = GraphicsEngine::GraphicsEngine::GetLibrary()->CreateSpritesheet(spritesheetCharacterTexture, Math::Vector2(16.0f, 16.0f));
}

void TestLayer::CreateScene() noexcept
{
	scene = std::shared_ptr<ECS::Scene>(new ECS::Scene("sandbox"));
	scene->Init();

	ECS::Entity entity = scene->CreateEntity("Mario");
	entity.AddComponent<ECS::CameraComponent>();
	entity.AddComponent<ECS::QuadComponent>();
	entity.AddComponent<ECS::SpriteComponent>();
	entity.AddComponent<ECS::StateMachine2DAnimationComponent>();
	entity.AddComponent<ECS::CppScriptComponent>().Bind<CameraController>();

	const float characterSpriteOffset = 0.001f;
	ECS::StateMachine2DAnimationComponent& stateMachineComponent = entity.GetComponent<ECS::StateMachine2DAnimationComponent>();
	
	ECS::State2DAnimation* idleState = new ECS::State2DAnimation("Idle");
	ECS::Frame2DAnimation idleFrame = ECS::Frame2DAnimation(
		spritesheetCharacter->GetSprite(Math::Vector2(0.0f, 1.0f), characterSpriteOffset),
		2.0
	);
	idleState->AddFrame(idleFrame);
	stateMachineComponent.AddState(idleState);

	const double runFrameTime = 0.150;
	ECS::State2DAnimation* runState = new ECS::State2DAnimation("Run");
	ECS::Frame2DAnimation runFrame1 = ECS::Frame2DAnimation(
		spritesheetCharacter->GetSprite(Math::Vector2(1.0f, 1.0f), characterSpriteOffset),
		runFrameTime
	);
	ECS::Frame2DAnimation runFrame2 = ECS::Frame2DAnimation(
		spritesheetCharacter->GetSprite(Math::Vector2(2.0f, 1.0f), characterSpriteOffset),
		runFrameTime
	);
	ECS::Frame2DAnimation runFrame3 = ECS::Frame2DAnimation(
		spritesheetCharacter->GetSprite(Math::Vector2(3.0f, 1.0f), characterSpriteOffset),
		runFrameTime
	);
	runState->AddFrame(runFrame1);
	runState->AddFrame(runFrame2);
	runState->AddFrame(runFrame3);
	stateMachineComponent.AddState(runState);

	stateMachineComponent.Play(runState->GetName());
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
