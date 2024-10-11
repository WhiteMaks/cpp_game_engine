#include "ECS/Registry.h"

namespace ECS
{

	std::shared_ptr<Entity> Registry::CreateEntity(Scene* scene, const std::string& name) noexcept
	{
		return std::shared_ptr<Entity>(new Entity(scene, name));
	}

	void Registry::DestroyEntity(const std::shared_ptr<Entity>& entity) noexcept
	{
	}

}