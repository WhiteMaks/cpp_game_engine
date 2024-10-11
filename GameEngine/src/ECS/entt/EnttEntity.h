#pragma once

#include <entt/entt.hpp>

#include "ECS/Entity.h"
#include "ECS/entt/EnttRegistry.h"

namespace ECS
{

	class EnttEntity : public Entity
	{
	private:
		entt::entity entity;

		friend EnttRegistry;

	public:
		EnttEntity(Scene* scene, const std::string& name, entt::entity entity) noexcept;
	};

}