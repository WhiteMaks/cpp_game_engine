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
	static float rotationAngle = 0.0f;
	rotationAngle += GameEngine::Time::GetDeltaTime() * 50;

	GraphicsEngine::Renderer::Clear();
	GraphicsEngine::Renderer::SetClearColor(Math::Vector4(0.2f, 0.2f, 0.2f, 1.0f));

	GraphicsEngine::Renderer2D::ResetStatistics();

	GraphicsEngine::Renderer2D::BeginScene(cameraController->GetCamera());
	
	float cubeSize = 50.0f;
	float offset = 0.05f;

	for (float y = -cubeSize; y < cubeSize; y = y + 0.5f)
	{
		for (float x = -cubeSize; x < cubeSize; x = x + 0.5f)
		{
			GraphicsEngine::Renderer2D::DrawQuad(Math::Vector3(x, y, -0.2f), Math::Vector2(0.45f, 0.45f), Math::Vector4((x + cubeSize) / (2 * cubeSize), (y + cubeSize) / (2 * cubeSize), (x + y + cubeSize) / (3 * cubeSize), 1.0f));
		}
	}

	GraphicsEngine::Renderer2D::DrawQuad(Math::Vector3(0.0f, 0.0f, -0.1f), Math::Vector3(0.0f, 0.0f, rotationAngle), Math::Vector2(0.5f, 0.5f), texture);
	GraphicsEngine::Renderer2D::DrawQuad(Math::Vector2(-1.0f, 0.0f), Math::Vector2(0.5f, 0.5f), Math::Vector4(1.0f, 0.0f, 1.0f, 1.0f));
	GraphicsEngine::Renderer2D::DrawQuad(Math::Vector2(1.0f, 0.0f), Math::Vector2(0.5f, 0.5f), Math::Vector4(0.0f, 0.0f, 1.0f, 1.0f));
	GraphicsEngine::Renderer2D::DrawQuad(Math::Vector2(0.0f, 0.0f), Math::Vector2(0.5f, 0.5f), texture2);


	GraphicsEngine::Renderer2D::EndScene();
	
	GraphicsEngine::Renderer2D::Statistics statistics = GraphicsEngine::Renderer2D::GetStatistics();

	APPLICATION_TRACE("Quads: {0}", statistics.quads);
	APPLICATION_TRACE("Vertex count: {0}", statistics.GetVertexCount());
	APPLICATION_TRACE("Index count: {0}", statistics.GetIndexCount());
	APPLICATION_TRACE("Textures: {0}", statistics.textures);
	APPLICATION_TRACE("Draw calls: {0}", statistics.drawCalls);

	APPLICATION_DEBUG("FPS: {0}", 1.0 / GameEngine::Time::GetDeltaTime());
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
