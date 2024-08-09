#include <GameEngine.h>

class TestLayer : public GameEngine::Layer
{
private:
	std::shared_ptr<GraphicsEngine::ShaderProgram> shaderProgram;
	std::shared_ptr<GraphicsEngine::VertexArrayBuffer> vertexArrayBuffer;
	std::shared_ptr<GraphicsEngine::Texture> texture;
	std::shared_ptr<GraphicsEngine::Texture> texture2;

	std::shared_ptr<GraphicsEngine::OrthographicCameraController> cameraController;

public:
	
	TestLayer()
		: Layer("Test layer")
	{

	}

	void Init() noexcept override
	{
		shaderProgram = std::shared_ptr<GraphicsEngine::ShaderProgram>(
			GraphicsEngine::ShaderProgramFactory::Create("assets/shaders/texture_shader")
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

		cameraController = std::shared_ptr<GraphicsEngine::OrthographicCameraController>(
			new GraphicsEngine::OrthographicCameraController(0.0f)
		);
		cameraController->Init();

		texture = std::shared_ptr<GraphicsEngine::Texture>(
			GraphicsEngine::TextureFactory::Create("assets/textures/checkerboard.png")
		);
		texture->Init();

		texture2 = std::shared_ptr<GraphicsEngine::Texture>(
			GraphicsEngine::TextureFactory::Create("assets/textures/butterfly.png")
		);
		texture2->Init();

		shaderProgram->SetUniformInt("u_Texture", 0);
	}

	void Update() noexcept override
	{
		cameraController->Update();
	}

	void Render() noexcept override
	{
		GraphicsEngine::Renderer::Clear();
		GraphicsEngine::Renderer::SetClearColor(Math::Vector4(0.2f, 0.2f, 0.2f, 1.0f));

		GraphicsEngine::Renderer::BeginScene(cameraController->GetCamera());

		//glm::mat4 scale = glm::scale(glm::mat4(1.0f), Math::Vector3(0.5f));
		//for (int y = -10; y < 10; y++)
		//{
		//	for (int x = -10; x < 10; x++)
		//	{
		//		glm::vec3 position(x * 0.11f, y * 0.11f, 0.0f);
		//		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position) * scale;
		//
		//		GraphicsEngine::Renderer::Submit(shaderProgram, vertexArrayBuffer, modelMatrix);
		//	}
		//}


		texture->Bind();
		GraphicsEngine::Renderer::Submit(shaderProgram, vertexArrayBuffer, glm::scale(glm::mat4(1.0f), Math::Vector3(1.0f)));
		texture->Unbind();

		texture2->Bind();
		GraphicsEngine::Renderer::Submit(shaderProgram, vertexArrayBuffer, glm::scale(glm::mat4(1.0f), Math::Vector3(1.0f)));
		texture2->Unbind();

		GraphicsEngine::Renderer::EndScene();

		//APPLICATION_DEBUG("FPS: {0}", 1.0 / GameEngine::Time::GetDeltaTime());
	}

	void MouseEvent(EventsSystem::MouseEvent& event) noexcept override
	{
		cameraController->MouseEvent(event);
	}

	void KeyboardEvent(EventsSystem::KeyboardEvent& event) noexcept override
	{
		cameraController->KeyboardEvent(event);
	}

	void WindowEvent(EventsSystem::WindowEvent& event) noexcept override
	{
		cameraController->WindowEvent(event);
	}

	void Destroy() noexcept override
	{
		vertexArrayBuffer->Destroy();
		shaderProgram->Destroy();
		cameraController->Destroy();
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