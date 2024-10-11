#include "ECS/Scene.h"

#include "ECS/RegistryFactory.h"

#include "Tools/Log.h"

namespace ECS
{
	Scene::Scene() noexcept
		: registry(RegistryFactory::Create())
	{
		
	}

	void Scene::Init() noexcept
	{
		
	}

	void Scene::Update() noexcept
	{
		
	}

	void Scene::Render() noexcept
	{
		
	}

	void Scene::Destroy() noexcept
	{
		
	}

	std::shared_ptr<Entity> Scene::CreateEntity(const std::string& name) noexcept
	{
		std::shared_ptr<Entity> entity = registry->CreateEntity(this, name);

		entities[name] = entity;

		return entity;
	}

	void Scene::DestroyEntity(const std::shared_ptr<Entity>& entity) noexcept
	{
		entities.erase(entity->GetName());
		registry->DestroyEntity(entity);
	}

}