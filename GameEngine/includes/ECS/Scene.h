#pragma once

#include <vector>
#include <memory>

#include "Entity.h"
#include "Core/Core.h"

namespace ECS
{

	class GAME_ENGINE_API Scene
	{
	private:
		std::vector<std::shared_ptr<Entity>> entities;

	public:
		void Init() noexcept;
		void Update() noexcept;
		void Render() noexcept;
		void Destroy() noexcept;

		std::shared_ptr<Entity> CreateEntity() noexcept;
	};

}