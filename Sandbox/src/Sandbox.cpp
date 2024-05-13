#include <GameEngine.h>

class TestLayer : public GameEngine::Layer
{
private:
	std::shared_ptr<GraphicsEngine::ShaderProgram> shaderProgram;
	std::shared_ptr<GraphicsEngine::VertexArrayBuffer> vertexArrayBuffer;

	GraphicsEngine::OrthographicCamera camera;

	float cameraSpeed = 0.5f;

public:
	
	TestLayer()
		: Layer("Test layer"), camera(-1.60f, 1.60f, -0.90f, 0.90f)
	{

	}

	void Init() noexcept override
	{
		std::string vertex = GraphicsEngine::ShaderCodeFactory::CreateDefaultVertexShader();
		std::string fragment = GraphicsEngine::ShaderCodeFactory::CreateDefaultFragmentShader();

		shaderProgram = std::shared_ptr<GraphicsEngine::ShaderProgram>(
			GraphicsEngine::ShaderProgramFactory::Create(vertex, fragment)
		);
		shaderProgram->Init();


		vertexArrayBuffer = std::shared_ptr<GraphicsEngine::VertexArrayBuffer>(
			GraphicsEngine::BufferFactory::CreateVertexArrayBuffer()
		);
		vertexArrayBuffer->Init();

		float vertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		std::shared_ptr<GraphicsEngine::VertexStaticBuffer> vertexBuffer = std::shared_ptr<GraphicsEngine::VertexStaticBuffer>(
			GraphicsEngine::BufferFactory::CreateVertexStaticBuffer(vertices, sizeof(vertices))
		);

		std::vector<GraphicsEngine::BufferElement> bufferElements = {
			{GraphicsEngine::BufferElementType::FLOAT_3, "a_Position"},
			{GraphicsEngine::BufferElementType::FLOAT_2, "a_TextureCoordinate"},
		};

		GraphicsEngine::BufferLayout bufferLayout(bufferElements);
		bufferLayout.Init();

		vertexBuffer->SetLayout(bufferLayout);
		vertexBuffer->Init();

		vertexArrayBuffer->AddVertexBuffer(vertexBuffer);

		unsigned int indices[6] = {
			0, 1, 2, 2, 3, 0
		};

		std::shared_ptr<GraphicsEngine::IndexStaticBuffer> indexBuffer = std::shared_ptr<GraphicsEngine::IndexStaticBuffer>(
			GraphicsEngine::BufferFactory::CreateIndexStaticBuffer(indices, sizeof(indices) / sizeof(unsigned int))
		);
		indexBuffer->Init();

		vertexArrayBuffer->SetIndexBuffer(indexBuffer);

		camera.SetPosition({ 0.0f, 0.0f, 0.0f });
		camera.SetRotation(0.0f);
	}

	void Update() noexcept override
	{
		if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyD))
		{
			camera.GetPosition().x += cameraSpeed * GameEngine::Time::GetDeltaTime();
		}

		if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyA))
		{
			camera.GetPosition().x -= (cameraSpeed * GameEngine::Time::GetDeltaTime());
		}

		if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyW))
		{
			camera.GetPosition().y += (cameraSpeed * GameEngine::Time::GetDeltaTime());
		}

		if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyS))
		{
			camera.GetPosition().y -= (cameraSpeed * GameEngine::Time::GetDeltaTime());
		}

		if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyE))
		{	
			camera.SetRotation(camera.GetRotation() - (cameraSpeed * GameEngine::Time::GetDeltaTime() * 30));
		}

		if (EventsSystem::EventManager::GetInstance()->GetKetboard()->KeyIsPressed(EventsSystem::EventManager::keyQ))
		{
			camera.SetRotation(camera.GetRotation() + (cameraSpeed * GameEngine::Time::GetDeltaTime() * 30));
		}

		camera.Update();
	}

	void Render() noexcept override
	{
		GraphicsEngine::Renderer::Clear();
		GraphicsEngine::Renderer::SetClearColor(Math::Vector4(0.2f, 0.2f, 0.2f, 1.0f));

		GraphicsEngine::Renderer::BeginScene(camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), Math::Vector3(0.1f));
		for (int y = -10; y < 10; y++)
		{
			for (int x = -10; x < 10; x++)
			{
				glm::vec3 position(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position) * scale;

				GraphicsEngine::Renderer::Submit(shaderProgram, vertexArrayBuffer, modelMatrix);
			}
		}

		GraphicsEngine::Renderer::Submit(shaderProgram, vertexArrayBuffer, glm::scale(glm::mat4(1.0f), Math::Vector3(1.5f)));

		GraphicsEngine::Renderer::EndScene();

		APPLICATION_DEBUG("FPS: {0}", 1.0 / GameEngine::Time::GetDeltaTime());
	}

	void MouseEvent(EventsSystem::MouseEvent& event) noexcept override
	{
	}

	void KeyboardEvent(EventsSystem::KeyboardEvent& event) noexcept override
	{
	}

	void Destroy() noexcept override
	{
		vertexArrayBuffer->Destroy();
		shaderProgram->Destroy();
	}
};

class Sandbox : public GameEngine::GameEngine
{
public:

	Sandbox()
		: GameEngine::GameEngine("Sandbox")
	{
		PushLayer(new TestLayer());
	}

	~Sandbox()
	{

	}
};

int main()
{
	Sandbox* sandbox = new Sandbox();
	
	sandbox->Start();
}
