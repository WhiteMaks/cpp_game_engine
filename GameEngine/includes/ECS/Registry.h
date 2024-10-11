#pragma once

#include <memory>

#include "Entity.h"

namespace ECS
{
	class Scene;

	class Registry
	{
	public:
		virtual std::shared_ptr<Entity> CreateEntity(Scene* scene, const std::string& name) noexcept;

		virtual void DestroyEntity(const std::shared_ptr<Entity>& entity) noexcept;

	};

}