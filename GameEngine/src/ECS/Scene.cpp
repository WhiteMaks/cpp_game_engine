#include "ECS/Scene.h"

#include "Tools/Log.h"

namespace ECS
{

	void Scene::Init() noexcept
	{
		
	}

	void Scene::Update() noexcept
	{
		//scriptSystem->Update();
	}

	void Scene::Render() noexcept
	{
		//spriteSystem->Render();
	}

	void Scene::Destroy() noexcept
	{
		
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