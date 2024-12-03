#pragma once

#include <string>
#include <unordered_map>
#include <entt/entt.hpp>

#include "Core/Core.h"
#include "Core/GraphicsEngine/Renderer/Camera.h"
#include "EventsSystem/KeyboardEvent.h"
#include "EventsSystem/WindowEvent.h"
#include "EventsSystem/MouseEvent.h"

#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/ColorComponent.h"
#include "ECS/Components/TextureComponent.h"
#include "ECS/Components/SpriteComponent.h"
#include "ECS/Components/CameraComponent.h"
#include "ECS/Components/QuadComponent.h"

namespace ECS
{

	class Entity;
	class CppScriptComponent;

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

		void RemoveEntity(Entity entity) noexcept;

		Entity CreateEntity(const std::string& name) noexcept;

	private:
		void RenderColorQuads() noexcept;
		void RenderTextureQuads() noexcept;
		void RenderSpriteQuads() noexcept;

		void UpdateCameraSystem() noexcept;
		void UpdateScriptSystem() noexcept;

		template<typename T>
		void OnComponentAdded(Entity entity, T& componet) noexcept;
		template<>
		void OnComponentAdded<QuadComponent>(Entity entity, QuadComponent& componet) noexcept;
		template<>
		void OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& componet) noexcept;
		template<>
		void OnComponentAdded<ColorComponent>(Entity entity, ColorComponent& componet) noexcept;
		template<>
		void OnComponentAdded<TextureComponent>(Entity entity, TextureComponent& componet) noexcept;
		template<>
		void OnComponentAdded<CppScriptComponent>(Entity entity, CppScriptComponent& componet) noexcept;
		template<>
		void OnComponentAdded<SpriteComponent>(Entity entity, SpriteComponent& componet) noexcept;
		template<>
		void OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& componet) noexcept;
		
		template<typename T>
		void OnComponentRemoved(Entity entity, T& componet) noexcept;
		template<>
		void OnComponentRemoved<QuadComponent>(Entity entity, QuadComponent& componet) noexcept;
		template<>
		void OnComponentRemoved<TransformComponent>(Entity entity, TransformComponent& componet) noexcept;
		template<>
		void OnComponentRemoved<ColorComponent>(Entity entity, ColorComponent& componet) noexcept;
		template<>
		void OnComponentRemoved<TextureComponent>(Entity entity, TextureComponent& componet) noexcept;
		template<>
		void OnComponentRemoved<CppScriptComponent>(Entity entity, CppScriptComponent& componet) noexcept;
		template<>
		void OnComponentRemoved<SpriteComponent>(Entity entity, SpriteComponent& componet) noexcept;
		template<>
		void OnComponentRemoved<CameraComponent>(Entity entity, CameraComponent& componet) noexcept;

		void InitCppScriptComponentIfNeed(CppScriptComponent& cppScriptComponent, entt::entity handle) noexcept;

		GraphicsEngine::Camera* FindPrimaryCamera() noexcept;
	};

}