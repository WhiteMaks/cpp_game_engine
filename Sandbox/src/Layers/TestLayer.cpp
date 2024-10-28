#include "Layers/TestLayer.h"

#include <glm/gtc/matrix_transform.hpp>

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

	spriteTest = spritesheetTinyTown->GetSprite(Math::Vector2(9.0f, 6.0f));
}

void TestLayer::CreateScene() noexcept
{
	scene = std::shared_ptr<ECS::Scene>(new ECS::Scene());
	scene->Init();

	class TestScript : public ECS::ScriptableEntity
	{
	private:
		float cameraSpeed = 0.5f;
		float aspectRatio = 0.0f;
		float zoom = 1.0f;

		ECS::CameraComponent* cameraComponent;
		ECS::TransformComponent* transformComponent;

	public:
		void Init() noexcept override
		{
			cameraComponent = &GetComponent<ECS::CameraComponent>();
			transformComponent = &GetComponent<ECS::TransformComponent>();
		}

		void Update() noexcept override
		{
			if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyD))
			{
				transformComponent->position.x += cameraSpeed * GameEngine::Time::GetDeltaTime();
			}

			if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyA))
			{
				transformComponent->position.x -= (cameraSpeed * GameEngine::Time::GetDeltaTime());
			}

			if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyW))
			{
				transformComponent->position.y += (cameraSpeed * GameEngine::Time::GetDeltaTime());
			}

			if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyS))
			{
				transformComponent->position.y -= (cameraSpeed * GameEngine::Time::GetDeltaTime());
			}

			if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyE))
			{
				transformComponent->rotation.z = (transformComponent->rotation.z - (cameraSpeed * GameEngine::Time::GetDeltaTime() * 30));
			}

			if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyQ))
			{
				transformComponent->rotation.z = (transformComponent->rotation.z + (cameraSpeed * GameEngine::Time::GetDeltaTime() * 30));
			}
		}

		void KeyboardEvent(EventsSystem::KeyboardEvent& keyboardEvent) noexcept override
		{
			if (keyboardEvent.GetCode() == EventsSystem::EventManager::keyR && keyboardEvent.IsPressed())
			{
				zoom--;
				zoom = std::max(zoom, 0.5f);
				cameraComponent->camera.SetProjectionMatrix(glm::ortho(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom, -1.0f, 1.0f));

				keyboardEvent.Invalidate();
			}

			if (keyboardEvent.GetCode() == EventsSystem::EventManager::keyF && keyboardEvent.IsPressed())
			{
				zoom++;
				cameraComponent->camera.SetProjectionMatrix(glm::ortho(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom, -1.0f, 1.0f));

				keyboardEvent.Invalidate();
			}
		}

		void WindowEvent(EventsSystem::WindowEvent& windowEvent) noexcept
		{
			if (windowEvent.GetType() == EventsSystem::WindowEventType::RESIZE)
			{
				aspectRatio = (float) windowEvent.GetWidth() / (float) windowEvent.GetHeight();
				cameraComponent->camera.SetProjectionMatrix(glm::ortho(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom, -1.0f, 1.0f));
			}
		}

		void Destroy() noexcept override
		{
		}
	};
	ECS::Entity cameraEntity = scene->CreateEntity("Camera");
	ECS::CameraComponent& cameraComponent = cameraEntity.AddComponent<ECS::CameraComponent>();
	cameraComponent.camera = GraphicsEngine::Camera(glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
	cameraEntity.AddComponent<ECS::CppScriptComponent>().Bind<TestScript>();

	ECS::Entity entity = scene->CreateEntity("test");
	ECS::SpriteComponent& spriteComponent = entity.AddComponent<ECS::SpriteComponent>();
	spriteComponent.sprite = spriteTest;
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
