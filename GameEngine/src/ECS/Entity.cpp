#include "ECS/Entity.h"

namespace ECS
{
	
	Entity::Entity() noexcept
		: Entity(nullptr, "")
	{
	}

	Entity::Entity(Scene* scene, const std::string& name) noexcept
		: scene(scene), name(name)
	{
	}

	const std::string& Entity::GetName() noexcept
	{
		return name;
	}

}