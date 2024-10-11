#pragma once

#include <string>

#include "Core/Core.h"

namespace ECS
{
	class Scene;

	class GAME_ENGINE_API Entity
	{
	private:
		std::string name;

	protected:
		Scene* scene;

	public:
		Entity() noexcept;
		Entity(Scene* scene, const std::string& name) noexcept;

		virtual ~Entity() = default;

	public:
		const std::string& GetName() noexcept;
	};

}