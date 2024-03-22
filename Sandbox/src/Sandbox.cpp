#include <GameEngine.h>

class Sandbox : public GameEngine::Engine
{
public:

	Sandbox()
		: GameEngine::Engine("Sandbox")
	{

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
	
	APPLICATION_INFO("Starting sandbox");
	sandbox->Start();
	APPLICATION_INFO("Sandbox stopped");

	delete sandbox;
}
