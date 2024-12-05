#include "ECS/Scene.h"

#include <fstream>
#include <filesystem>

#include <glm/gtc/matrix_transform.hpp>
#include <yaml-cpp/yaml.h>

#include "Tools/Log.h"
#include "ECS/Entity.h"
#include "Core/GraphicsEngine/Renderer/Renderer2D.h"

#include "ECS/Components/CppScriptComponent.h"

namespace ECS
{
	Scene::Scene() noexcept
	{
		
	}

	void Scene::Init() noexcept
	{
		
	}

	void Scene::MouseEvent(EventsSystem::MouseEvent& mouseEvent) noexcept
	{
		auto group = registry.group<CppScriptComponent>();
		for (auto entity : group)
		{
			if (!mouseEvent.IsValid())
			{
				break;
			}

			auto& cppScriptComponent = group.get<CppScriptComponent>(entity);
			InitCppScriptComponentIfNeed(cppScriptComponent, entity);

			cppScriptComponent.instance->MouseEvent(mouseEvent);
		}
	}

	void Scene::KeyboardEvent(EventsSystem::KeyboardEvent& keyboardEvent) noexcept
	{
		auto group = registry.group<CppScriptComponent>();
		for (auto entity : group)
		{
			if (!keyboardEvent.IsValid())
			{
				break;
			}

			auto& cppScriptComponent = group.get<CppScriptComponent>(entity);
			InitCppScriptComponentIfNeed(cppScriptComponent, entity);

			cppScriptComponent.instance->KeyboardEvent(keyboardEvent);
		}
	}

	void Scene::WindowEvent(EventsSystem::WindowEvent& windowEvent) noexcept
	{
		auto group = registry.group<CppScriptComponent>();
		for (auto entity : group)
		{
			if (!windowEvent.IsValid())
			{
				break;
			}

			auto& cppScriptComponent = group.get<CppScriptComponent>(entity);
			InitCppScriptComponentIfNeed(cppScriptComponent, entity);

			cppScriptComponent.instance->WindowEvent(windowEvent);
		}
	}

	void Scene::Update() noexcept
	{
		UpdateCameraSystem();
		UpdateScriptSystem();
	}

	void Scene::Render() noexcept
	{
		GraphicsEngine::Camera* primaryCamera = FindPrimaryCamera();
		
		if (!primaryCamera)
		{
			return;
		}

		GraphicsEngine::Renderer2D::BeginScene(*primaryCamera);
		RenderColorQuads();
		RenderTextureQuads();
		RenderSpriteQuads();
		GraphicsEngine::Renderer2D::EndScene();
	}

	void Scene::Destroy() noexcept
	{
		auto group = registry.group<CppScriptComponent>();
		for (auto entity : group)
		{
			auto cppScriptComponent = group.get<CppScriptComponent>(entity);
			if (cppScriptComponent.instance)
			{
				cppScriptComponent.instance->Destroy();
			}

			cppScriptComponent.DestroyScript(&cppScriptComponent);
		}

		for (auto entity : registry.view<entt::entity>())
		{
			registry.destroy(entity);
		}
	}

	void Scene::SaveInYaml(const std::string& filePath) noexcept
	{
		YAML::Emitter yamlData;
		
		yamlData << YAML::BeginMap;
		
		yamlData << YAML::Key << "Scene";
		yamlData << YAML::Value << "Test name scene";

		yamlData << YAML::Key << "Entities";
		yamlData << YAML::Value << YAML::BeginSeq;
		for (auto entity : registry.view<entt::entity>())
		{
			SaveEntityInYaml(yamlData, Entity(entity, this));
		}
		yamlData << YAML::Value << YAML::EndSeq;

		yamlData << YAML::EndMap;

		std::filesystem::path path(filePath);
		std::filesystem::path directory = path.parent_path();
		if (!directory.empty() && !std::filesystem::exists(directory))
		{
			std::filesystem::create_directories(directory);
		}

		std::ofstream yamlFile(filePath);
		yamlFile << yamlData.c_str();
		yamlFile.close();
	}

	void Scene::LoadFromYaml(const std::string& filePath) noexcept
	{
	}

	Entity Scene::CreateEntity(const std::string& name) noexcept
	{
		Entity result(registry.create(), this);

		TransformComponent& transform = result.AddComponent<TransformComponent>();
		transform.position = Math::Vector3();
		transform.rotation = Math::Vector3();
		transform.scale = Math::Vector3(1.0f);

		return result;
	}

	void Scene::RenderColorQuads() noexcept
	{
		auto view = registry.view<QuadComponent, TransformComponent, ColorComponent>();
		for (auto entity : view)
		{
			auto [transformComponent, colorComponent] = view.get<TransformComponent, ColorComponent>(entity);
			GraphicsEngine::Renderer2D::DrawQuad(transformComponent.position, transformComponent.rotation, transformComponent.scale, colorComponent.color);
		}
	}

	void Scene::RenderTextureQuads() noexcept
	{
		auto view = registry.view<QuadComponent, TransformComponent, TextureComponent>();
		for (auto entity : view)
		{
			auto [transformComponent, textureComponent] = view.get<TransformComponent, TextureComponent>(entity);
			GraphicsEngine::Renderer2D::DrawQuad(transformComponent.position, transformComponent.rotation, transformComponent.scale, textureComponent.texture);
		}
	}

	void Scene::RenderSpriteQuads() noexcept
	{
		auto view = registry.view<QuadComponent, TransformComponent, SpriteComponent>();
		for (auto entity : view)
		{
			auto [transformComponent, spriteComponent] = view.get<TransformComponent, SpriteComponent>(entity);
			GraphicsEngine::Renderer2D::DrawSprite(transformComponent.position, transformComponent.rotation, transformComponent.scale, spriteComponent.sprite);
		}
	}

	void Scene::UpdateCameraSystem() noexcept
	{
		auto view = registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view)
		{
			auto transformComponent = view.get<TransformComponent>(entity);
			auto& cameraComponent = view.get<CameraComponent>(entity);

			if (cameraComponent.primary)
			{
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), transformComponent.position) *
					glm::rotate(glm::mat4(1.0f), glm::radians(transformComponent.rotation.z), Math::Vector3(0, 0, 1));

				cameraComponent.camera.SetViewMatrix(glm::inverse(transform));
				cameraComponent.camera.Update();
				break;
			}
		}
	}

	void Scene::UpdateScriptSystem() noexcept
	{
		auto group = registry.group<CppScriptComponent>();
		for (auto entity : group)
		{
			auto& cppScriptComponent = group.get<CppScriptComponent>(entity);
			InitCppScriptComponentIfNeed(cppScriptComponent, entity);

			cppScriptComponent.instance->Update();
		}
	}

	void Scene::InitCppScriptComponentIfNeed(CppScriptComponent& cppScriptComponent, entt::entity handle) noexcept
	{
		if (!cppScriptComponent.instance)
		{
			cppScriptComponent.instance = cppScriptComponent.InitScript();
			cppScriptComponent.instance->entity = Entity(handle, this);
			cppScriptComponent.instance->Init();
		}
	}

	GraphicsEngine::Camera* Scene::FindPrimaryCamera() noexcept
	{
		auto view = registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view)
		{
			auto [transformComponent, cameraComponent] = view.get<TransformComponent, CameraComponent>(entity);

			if (cameraComponent.primary)
			{
				return &cameraComponent.camera;
			}
		}

		return nullptr;
	}

	void Scene::RemoveEntity(Entity entity) noexcept
	{
		if (entity.HasComponent<CppScriptComponent>())
		{
			auto cppScriptComponent = entity.GetComponent<CppScriptComponent>();
			if (cppScriptComponent.instance)
			{
				cppScriptComponent.instance->Destroy();
			}

			cppScriptComponent.DestroyScript(&cppScriptComponent);
		}
		
		if (registry.valid(entity))
		{
			registry.destroy(entity);
		}
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& componet) noexcept
	{
	}

	template<>
	void Scene::OnComponentAdded<QuadComponent>(Entity entity, QuadComponent& componet) noexcept
	{
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& componet) noexcept
	{
	}

	template<>
	void Scene::OnComponentAdded(Entity entity, ColorComponent& componet) noexcept
	{
	}

	template<>
	void Scene::OnComponentAdded(Entity entity, TextureComponent& componet) noexcept
	{
	}

	template<>
	void Scene::OnComponentAdded<CppScriptComponent>(Entity entity, CppScriptComponent& componet) noexcept
	{
	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& componet) noexcept
	{
	}

	template<>
	void Scene::OnComponentAdded<SpriteComponent>(Entity entity, SpriteComponent& componet) noexcept
	{
	}

	template<typename T>
	void Scene::OnComponentRemoved(Entity entity, T& componet) noexcept
	{
	}

	template<>
	void Scene::OnComponentRemoved(Entity entity, QuadComponent& componet) noexcept
	{
	}

	template<>
	void Scene::OnComponentRemoved(Entity entity, TransformComponent& componet) noexcept
	{
	}

	template<>
	void Scene::OnComponentRemoved(Entity entity, ColorComponent& componet) noexcept
	{
	}

	template<>
	void Scene::OnComponentRemoved(Entity entity, TextureComponent& componet) noexcept
	{
	}

	template<>
	void Scene::OnComponentRemoved(Entity entity, CppScriptComponent& componet) noexcept
	{
		componet.instance->Destroy();
		componet.DestroyScript(&componet);
	}

	template<>
	void Scene::OnComponentRemoved(Entity entity, SpriteComponent& componet) noexcept
	{
	}

	template<>
	void Scene::OnComponentRemoved(Entity entity, CameraComponent& componet) noexcept
	{
	}

	void Scene::SaveEntityInYaml(YAML::Emitter& yamlData, Entity entity) noexcept
	{
		yamlData << YAML::BeginMap;

		yamlData << YAML::Key << "ID";
		yamlData << YAML::Value << "Test entity id";

		if (entity.HasComponent<TransformComponent>())
		{
			auto& transformComponent = entity.GetComponent<TransformComponent>();

			yamlData << YAML::Key << "TransformComponent";
			yamlData << YAML::BeginMap;

			yamlData << YAML::Key << "Position";
			yamlData << YAML::BeginMap;

			yamlData << YAML::Key << "X";
			yamlData << YAML::Value << transformComponent.position.x;
			yamlData << YAML::Key << "Y";
			yamlData << YAML::Value << transformComponent.position.y;
			yamlData << YAML::Key << "Z";
			yamlData << YAML::Value << transformComponent.position.z;

			yamlData << YAML::EndMap;

			yamlData << YAML::Key << "Rotation";
			yamlData << YAML::BeginMap;

			yamlData << YAML::Key << "X";
			yamlData << YAML::Value << transformComponent.rotation.x;
			yamlData << YAML::Key << "Y";
			yamlData << YAML::Value << transformComponent.rotation.y;
			yamlData << YAML::Key << "Z";
			yamlData << YAML::Value << transformComponent.rotation.z;

			yamlData << YAML::EndMap;

			yamlData << YAML::Key << "Scale";
			yamlData << YAML::BeginMap;

			yamlData << YAML::Key << "X";
			yamlData << YAML::Value << transformComponent.scale.x;
			yamlData << YAML::Key << "Y";
			yamlData << YAML::Value << transformComponent.scale.y;
			yamlData << YAML::Key << "Z";
			yamlData << YAML::Value << transformComponent.scale.z;

			yamlData << YAML::EndMap;

			yamlData << YAML::EndMap;
		}

		yamlData << YAML::EndMap;
	}

}