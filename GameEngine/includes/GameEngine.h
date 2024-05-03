#pragma once

#include <memory>

#include "Core/Core.h"

#include "Core/EventsSystem/EventManager.h"

#include "Core/GraphicsEngine/GraphicsEngine.h"

#include "Tools/Log.h"
#include "Tools/Layer.h"
#include "Tools/Time.h"
#include "Tools/LayerStack.h"

#include "Tools/Math/Vector.h"
#include "Tools/Math/Vector2.h"
#include "Tools/Math/Vector3.h"
#include "Tools/Math/Vector4.h"

namespace GameEngine
{

	class GAME_ENGINE_API GameEngine
	{
	private:
		GraphicsEngine::GraphicsEngine* graphicsEngine;
		EventsSystem::EventManager* eventManager;
		LayerStack* layerStack;

	public:
		GameEngine(const std::string& applicationTitle, const unsigned int applicationWidth = 1280, const unsigned int applicationHeight = 720);
		
		virtual ~GameEngine();

	public:
		void Loop();
		void Start();

	protected:
		void PushLayer(Layer* layer);
		void PushOverlayLayer(Layer* layer);

	private:
		void Init();
		void StartLoop();
		void Input();
		void Update();
		void Render();
		void Destroy();

	};

}