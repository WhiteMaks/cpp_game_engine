#pragma once

#include <string>
#include <unordered_map>
#include <entt/entt.hpp>

#include "Core/Core.h"
#include "Core/GraphicsEngine/Renderer/Camera.h"
#include "EventsSystem/KeyboardEvent.h"
#include "EventsSystem/WindowEvent.h"
#include "EventsSystem/MouseEvent.h"

namespace ECS
{

	class Entity;

	class GAME_ENGINE_API Scene
	{
	private:
		entt::registry registry;

		std::unordered_map<std::string, entt::entity> entities;

		friend class Entity;

	public:
		Scene() noexcept;

	public:
		void Init() noexcept;
		void MouseEvent(EventsSystem::MouseEvent& mouseEvent) noexcept;
		void KeyboardEvent(EventsSystem::KeyboardEvent& keyboardEvent) noexcept;
		void WindowEvent(EventsSystem::WindowEvent& windowEvent) noexcept;
		void Update() noexcept;
		void Render() noexcept;
		void Destroy() noexcept;

		void DestroyEntity(Entity entity) noexcept;

		Entity CreateEntity(const std::string& name) noexcept;

	private:
		void RenderColorQuads() noexcept;
		void RenderTextureQuads() noexcept;
		void RenderSpriteQuads() noexcept;

		void UpdateCameraSystem() noexcept;

		GraphicsEngine::Camera* FindPrimaryCamera() noexcept;
	};

}