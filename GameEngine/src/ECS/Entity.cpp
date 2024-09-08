#include "ECS/Entity.h"

namespace ECS
{

	Entity::Entity(const unsigned int id) noexcept
		: id(id)
	{
	}

	const unsigned int Entity::GetId() noexcept
	{
		return id;
	}

}