#pragma once

#include <memory>

#include "Core/Core.h"
#include "Core/OrthographicCameraController.h"

#include "Core/GraphicsEngine/GraphicsEngine.h"

#include "EventsSystem/EventManager.h"

#include "ECS/Scene.h"
#include "ECS/Entity.h"

#include "Math/Vector.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

#include "Memory/CacheStorage.h"
#include "Memory/TimedCache.h"

#include "Tools/Log.h"
#include "Tools/Layer.h"
#include "Tools/Time.h"
#include "Tools/LayerStack.h"

namespace GameEngine
{

	class GAME_ENGINE_API GameEngine
	{
	private:
		static std::shared_ptr<Memory::TimedCache> timedCache;

	private:
		GraphicsEngine::GraphicsEngine* graphicsEngine;
		EventsSystem::EventManager* eventManager;
		LayerStack* layerStack;

	public:
		GameEngine(const std::string& applicationTitle, const unsigned int applicationWidth = 1280, const unsigned int applicationHeight = 720);
		
		virtual ~GameEngine();

	public:
		static std::shared_ptr<Memory::TimedCache> GetTimedCache();

	public:
		void Start();
		void Loop();

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