#include <GameEngine.h>

#include "Layers/TestLayer.h"

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