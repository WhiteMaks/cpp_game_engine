#include <GameEngine.h>

class TestLayer : public GameEngine::Layer
{
public:
	
	TestLayer()
		: Layer("Test layer")
	{

	}

	void Update() noexcept
	{
	}

	void MouseEvent(EventsSystem::MouseEvent& event) noexcept
	{
	}

	void KeyboardEvent(EventsSystem::KeyboardEvent& event) noexcept
	{
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
