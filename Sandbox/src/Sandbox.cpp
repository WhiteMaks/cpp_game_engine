#include <GameEngine.h>

class TestLayer : public GameEngine::Layer
{
private:
	std::shared_ptr<GraphicsEngine::ShaderProgram> shaderProgram;
	std::shared_ptr<GraphicsEngine::VertexArrayBuffer> vertexArrayBuffer;

	GraphicsEngine::OrthographicCamera camera;

public:
	
	TestLayer()
		: Layer("Test layer"), camera(-2.0f, 2.0f, -2.0f, 2.0f)
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

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<GraphicsEngine::VertexStaticBuffer> vertexBuffer = std::shared_ptr<GraphicsEngine::VertexStaticBuffer>(
			GraphicsEngine::BufferFactory::CreateVertexStaticBuffer(vertices, sizeof(vertices))
		);

		std::vector<GraphicsEngine::BufferElement> bufferElements = {
			{GraphicsEngine::BufferElementType::FLOAT_3, "a_Position"},
			{GraphicsEngine::BufferElementType::FLOAT_4, "a_Color"},
		};

		GraphicsEngine::BufferLayout bufferLayout(bufferElements);
		bufferLayout.Init();

		vertexBuffer->SetLayout(bufferLayout);
		vertexBuffer->Init();

		vertexArrayBuffer->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = {
			0, 1, 2
		};

		std::shared_ptr<GraphicsEngine::IndexStaticBuffer> indexBuffer = std::shared_ptr<GraphicsEngine::IndexStaticBuffer>(
			GraphicsEngine::BufferFactory::CreateIndexStaticBuffer(indices, sizeof(indices) / sizeof(unsigned int))
		);
		indexBuffer->Init();

		vertexArrayBuffer->SetIndexBuffer(indexBuffer);
	}

	void Update() noexcept override
	{
		APPLICATION_DEBUG("FPS: [{0}]", 1.0 / GameEngine::Time::GetDeltaTime());
	}

	void Render() noexcept override
	{
		GraphicsEngine::Renderer::Clear();
		GraphicsEngine::Renderer::SetClearColor(Math::Vector4(0.2f, 0.2f, 0.2f, 1.0f));

		camera.SetPosition({ 0.5f, 0.5f, 0.0f });
		camera.SetRotation(45.0f);

		GraphicsEngine::Renderer::BeginScene(camera);
		GraphicsEngine::Renderer::Submit(shaderProgram, vertexArrayBuffer);
		GraphicsEngine::Renderer::EndScene();
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
