#include "ECS/RegistryFactory.h"

#include "ECS/entt/EnttRegistry.h"

namespace ECS
{

	std::shared_ptr<Registry> RegistryFactory::Create() noexcept
	{
		return std::shared_ptr<Registry>(new EnttRegistry());
	}

}