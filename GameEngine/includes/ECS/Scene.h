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

namespace YAML
{
	class Emitter;
}

namespace ECS
{

	class Entity;
	class CppScriptComponent;

	class GAME_ENGINE_API Scene
	{
	private:
		std::string name;
		entt::registry registry;

		friend class Entity;

	public:
		Scene(const std::string& name) noexcept;

	public:
		void Init() noexcept;
		void MouseEvent(EventsSystem::MouseEvent& mouseEvent) noexcept;
		void KeyboardEvent(EventsSystem::KeyboardEvent& keyboardEvent) noexcept;
		void WindowEvent(EventsSystem::WindowEvent& windowEvent) noexcept;
		void Update() noexcept;
		void Render() noexcept;
		void Destroy() noexcept;

		void SaveInYaml(const std::string& filePath) noexcept;
		void LoadFromYaml(const std::string& filePath) noexcept;

		void RemoveEntity(Entity entity) noexcept;

		Entity CreateEntity(const std::string& name) noexcept;

	private:
		void RenderColorQuads() noexcept;
		void RenderTextureQuads() noexcept;
		void RenderSpriteQuads() noexcept;

		void UpdateCameraSystem() noexcept;
		void UpdateScriptSystem() noexcept;

		template<typename T>
		void OnComponentAdded(Entity entity, T& component) noexcept;
		template<>
		void OnComponentAdded<QuadComponent>(Entity entity, QuadComponent& component) noexcept;
		template<>
		void OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component) noexcept;
		template<>
		void OnComponentAdded<ColorComponent>(Entity entity, ColorComponent& component) noexcept;
		template<>
		void OnComponentAdded<TextureComponent>(Entity entity, TextureComponent& component) noexcept;
		template<>
		void OnComponentAdded<CppScriptComponent>(Entity entity, CppScriptComponent& component) noexcept;
		template<>
		void OnComponentAdded<SpriteComponent>(Entity entity, SpriteComponent& component) noexcept;
		template<>
		void OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component) noexcept;
		
		template<typename T>
		void OnComponentRemoved(Entity entity, T& component) noexcept;
		template<>
		void OnComponentRemoved<QuadComponent>(Entity entity, QuadComponent& component) noexcept;
		template<>
		void OnComponentRemoved<TransformComponent>(Entity entity, TransformComponent& component) noexcept;
		template<>
		void OnComponentRemoved<ColorComponent>(Entity entity, ColorComponent& component) noexcept;
		template<>
		void OnComponentRemoved<TextureComponent>(Entity entity, TextureComponent& component) noexcept;
		template<>
		void OnComponentRemoved<CppScriptComponent>(Entity entity, CppScriptComponent& component) noexcept;
		template<>
		void OnComponentRemoved<SpriteComponent>(Entity entity, SpriteComponent& component) noexcept;
		template<>
		void OnComponentRemoved<CameraComponent>(Entity entity, CameraComponent& component) noexcept;

		void InitCppScriptComponentIfNeed(CppScriptComponent& cppScriptComponent, entt::entity handle) noexcept;

		void SaveEntityInYaml(YAML::Emitter& yamlData, Entity entity) noexcept;

		void SaveComponentInYaml(YAML::Emitter& yamlData, QuadComponent& component) noexcept;
		void SaveComponentInYaml(YAML::Emitter& yamlData, TransformComponent& component) noexcept;
		void SaveComponentInYaml(YAML::Emitter& yamlData, ColorComponent& component) noexcept;
		void SaveComponentInYaml(YAML::Emitter& yamlData, TextureComponent& component) noexcept;
		void SaveComponentInYaml(YAML::Emitter& yamlData, CppScriptComponent& component) noexcept;
		void SaveComponentInYaml(YAML::Emitter& yamlData, SpriteComponent& component) noexcept;
		void SaveComponentInYaml(YAML::Emitter& yamlData, CameraComponent& component) noexcept;

		void SaveVectorInYaml(YAML::Emitter& yamlData, const std::string& key, Math::Vector2 vector) noexcept;
		void SaveVectorInYaml(YAML::Emitter& yamlData, const std::string& key, Math::Vector3 vector) noexcept;
		void SaveVectorInYaml(YAML::Emitter& yamlData, const std::string& key, Math::Vector4 vector) noexcept;

		GraphicsEngine::Camera* FindPrimaryCamera() noexcept;
	};

}