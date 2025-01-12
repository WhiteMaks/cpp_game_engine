#include "ECS/Entity.h"

namespace ECS
{
	Entity::Entity() noexcept
		: Entity(entt::null, nullptr)
	{
	}

	Entity::Entity(entt::entity handle, Scene* scene) noexcept
		: handle(handle), scene(scene)
	{
	}

	Entity::operator entt::entity() const
	{
		return handle;
	}

	Scene* Entity::GetScene() noexcept
	{
		return scene;
	}

}