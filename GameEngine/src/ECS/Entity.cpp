#include "ECS/Entity.h"

namespace ECS
{
	Entity::Entity() noexcept
		: Entity(entt::null, nullptr, "")
	{
	}

	Entity::Entity(entt::entity handle, Scene* scene, const std::string& name) noexcept
		: handle(handle), scene(scene), name(name)
	{
	}

	Entity::operator entt::entity() const
	{
		return handle;
	}

	const std::string& Entity::GetName() noexcept
	{
		return name;
	}

}