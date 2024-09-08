#pragma once

#include <vector>
#include <set>
#include <memory>

#include "Entity.h"
#include "Systems/System.h"
#include "Core/Core.h"

namespace ECS
{

	class GAME_ENGINE_API Scene
	{
	private:
		std::vector<std::shared_ptr<Entity>> entities;
		std::vector<std::shared_ptr<System>> systems;

	public:
		Scene() noexcept;

	public:
		void Init() noexcept;
		void Update() noexcept;
		void Render() noexcept;
		void Destroy() noexcept;

		std::shared_ptr<Entity> CreateEntity() noexcept;
	};

}