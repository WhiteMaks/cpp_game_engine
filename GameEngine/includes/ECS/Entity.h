#pragma once

#include <string>
#include <entt/entt.hpp>

#include "Core/Core.h"
#include "Scene.h"

namespace ECS
{

	class GAME_ENGINE_API Entity
	{
	private:
		entt::entity handle;
		Scene* scene;

	public:
		Entity() noexcept;
		Entity(entt::entity handle, Scene* scene) noexcept;

		virtual ~Entity() = default;

	public:
		operator entt::entity() const;

	public:
		Scene* GetScene() noexcept;

	public:
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) noexcept
		{
			T& result = scene->registry.emplace<T>(handle, std::forward<Args>(args)...);
			scene->OnComponentAdded<T>(*this, result);
			return result;
		}

		template<typename T>
		T& GetComponent()
		{
			return scene->registry.get<T>(handle);
		}

		template<typename T>
		bool HasComponent()
		{
			return scene->registry.all_of<T>(handle);
		}

		template<typename T>
		void RemoveComponent()
		{
			scene->OnComponentRemoved<T>(*this, GetComponent<T>());
			scene->registry.remove<T>(handle);
		}

	};

}