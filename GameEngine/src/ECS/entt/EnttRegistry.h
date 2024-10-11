#pragma once 

#include <entt/entt.hpp>

#include "ECS/Registry.h"

namespace ECS
{

	class EnttRegistry : public Registry
	{
	private:
		entt::registry registry;

	public:
		EnttRegistry() noexcept;

		std::shared_ptr<Entity> CreateEntity(Scene* scene, const std::string& name) noexcept override;

		void DestroyEntity(const std::shared_ptr<Entity>& entity) noexcept override;
	};

}