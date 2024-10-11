#include "ECS/entt/EnttRegistry.h"

#include "ECS/entt/EnttEntity.h"

#include "Tools/Log.h"

namespace ECS
{

	EnttRegistry::EnttRegistry() noexcept
	{
		
	}

	std::shared_ptr<Entity> EnttRegistry::CreateEntity(Scene* scene, const std::string& name) noexcept
	{
		return std::shared_ptr<Entity>(new EnttEntity(scene, name, registry.create()));
	}

	void EnttRegistry::DestroyEntity(const std::shared_ptr<Entity>& entity) noexcept
	{
		if (auto enttEntity = std::dynamic_pointer_cast<EnttEntity>(entity))
		{
			registry.destroy(enttEntity->entity);
		}
	}

}