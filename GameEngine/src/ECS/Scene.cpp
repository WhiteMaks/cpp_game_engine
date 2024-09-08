#include "ECS/Scene.h"

#include "ECS/Systems/ColorSystem.h"
#include "Tools/Log.h"

namespace ECS
{
	Scene::Scene() noexcept
	{
		systems.push_back(std::make_shared<ColorSystem>());
	}

	void Scene::Init() noexcept
	{
		for (std::shared_ptr<System> system : systems)
		{
			system->Init();
		}
	}

	void Scene::Update() noexcept
	{
		for (std::shared_ptr<System> system : systems)
		{
			system->Update();
		}
	}

	void Scene::Render() noexcept
	{
		for (std::shared_ptr<System> system : systems)
		{
			system->Render();
		}
	}

	void Scene::Destroy() noexcept
	{
		for (std::shared_ptr<System> system : systems)
		{
			system->Destroy();
		}
	}

	std::shared_ptr<Entity> Scene::CreateEntity() noexcept
	{
		std::shared_ptr<Entity> result = std::shared_ptr<Entity>(
			new Entity(entities.size() + 1)
		);
		
		entities.push_back(result);

		return result;
	}

}