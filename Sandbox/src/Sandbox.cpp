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

class Sandbox : public GameEngine::Engine
{
public:

	Sandbox()
		: GameEngine::Engine("Sandbox")
	{
		PushLayer(new TestLayer());
	}

	~Sandbox()
	{

	}
};

int main()
{
	GameEngine::Log::Init();

	//docker run --rm -v ${PWD}:/src emscripten/emsdk emcc Sandbox/src/Sandbox.cpp -o helloworld.js -I GameEngine/src -D GAME_ENGINE_PLATFORM_BROWSER
	Sandbox* sandbox = new Sandbox();
	
	sandbox->Start();
}
