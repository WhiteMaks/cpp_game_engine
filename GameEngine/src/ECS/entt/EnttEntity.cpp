#include "EnttEntity.h"

namespace ECS
{

	EnttEntity::EnttEntity(Scene* scene, const std::string& name, entt::entity entity) noexcept
		: Entity(scene, name), entity(entity)
	{
	}

}