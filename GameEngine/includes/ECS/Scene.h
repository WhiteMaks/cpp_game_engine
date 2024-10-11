#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "Registry.h"
#include "Core/Core.h"

namespace ECS
{

	class GAME_ENGINE_API Scene
	{
	private:
		std::shared_ptr<Registry> registry;

		std::unordered_map<std::string, std::shared_ptr<Entity>> entities;

	public:
		Scene() noexcept;

	public:
		void Init() noexcept;
		void Update() noexcept;
		void Render() noexcept;
		void Destroy() noexcept;

		std::shared_ptr<Entity> CreateEntity(const std::string& name) noexcept;

		void DestroyEntity(const std::shared_ptr<Entity>& entity) noexcept;
	};

}