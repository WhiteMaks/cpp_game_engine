#include "ECS/Scene.h"

#include <fstream>
#include <filesystem>

#include <glm/gtc/matrix_transform.hpp>
#include <yaml-cpp/yaml.h>

#include "Tools/Log.h"
#include "ECS/Entity.h"
#include "Core/GraphicsEngine/Library/Renderer2D.h"

#include "ECS/Components/CppScriptComponent.h"

namespace ECS
{
	Scene::Scene(const std::string& name) noexcept
		: name(name)
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
			yamlData << YAML::Key << "name";
			yamlData << YAML::Value << name;

			yamlData << YAML::Key << "entities";
			yamlData << YAML::Value << YAML::BeginSeq;
				for (auto entity : registry.view<entt::entity>())
				{
					SaveEntityInYaml(yamlData, Entity(entity, this));
				}
			yamlData << YAML::Value << YAML::EndSeq;
		yamlData << YAML::EndMap;

		std::filesystem::path path(filePath + name + ".cpge");
		std::filesystem::path directory = path.parent_path();
		if (!directory.empty() && !std::filesystem::exists(directory))
		{
			std::filesystem::create_directories(directory);
		}

		std::ofstream yamlFile(filePath + name + ".cpge");
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
	void Scene::OnComponentAdded(Entity entity, T& component) noexcept
	{
	}

	template<>
	void Scene::OnComponentAdded<QuadComponent>(Entity entity, QuadComponent& component) noexcept
	{
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component) noexcept
	{
	}

	template<>
	void Scene::OnComponentAdded(Entity entity, ColorComponent& component) noexcept
	{
	}

	template<>
	void Scene::OnComponentAdded(Entity entity, TextureComponent& component) noexcept
	{
	}

	template<>
	void Scene::OnComponentAdded<CppScriptComponent>(Entity entity, CppScriptComponent& component) noexcept
	{
	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component) noexcept
	{
	}

	template<>
	void Scene::OnComponentAdded<SpriteComponent>(Entity entity, SpriteComponent& component) noexcept
	{
	}

	template<typename T>
	void Scene::OnComponentRemoved(Entity entity, T& component) noexcept
	{
	}

	template<>
	void Scene::OnComponentRemoved(Entity entity, QuadComponent& component) noexcept
	{
	}

	template<>
	void Scene::OnComponentRemoved(Entity entity, TransformComponent& component) noexcept
	{
	}

	template<>
	void Scene::OnComponentRemoved(Entity entity, ColorComponent& component) noexcept
	{
	}

	template<>
	void Scene::OnComponentRemoved(Entity entity, TextureComponent& component) noexcept
	{
	}

	template<>
	void Scene::OnComponentRemoved(Entity entity, CppScriptComponent& component) noexcept
	{
		component.instance->Destroy();
		component.DestroyScript(&component);
	}

	template<>
	void Scene::OnComponentRemoved(Entity entity, SpriteComponent& component) noexcept
	{
	}

	template<>
	void Scene::OnComponentRemoved(Entity entity, CameraComponent& component) noexcept
	{
	}

	void Scene::SaveEntityInYaml(YAML::Emitter& yamlData, Entity entity) noexcept
	{
		yamlData << YAML::BeginMap;
			yamlData << YAML::Key << "id";
			yamlData << YAML::Value << "123abc";

			if (entity.HasComponent<QuadComponent>())
			{
				SaveComponentInYaml(yamlData, entity.GetComponent<QuadComponent>());
			}

			if (entity.HasComponent<TransformComponent>())
			{
				SaveComponentInYaml(yamlData, entity.GetComponent<TransformComponent>());
			}

			if (entity.HasComponent<ColorComponent>())
			{
				SaveComponentInYaml(yamlData, entity.GetComponent<ColorComponent>());
			}

			if (entity.HasComponent<TextureComponent>())
			{
				SaveComponentInYaml(yamlData, entity.GetComponent<TextureComponent>());
			}

			if (entity.HasComponent<SpriteComponent>())
			{
				SaveComponentInYaml(yamlData, entity.GetComponent<SpriteComponent>());
			}

			if (entity.HasComponent<CameraComponent>())
			{
				SaveComponentInYaml(yamlData, entity.GetComponent<CameraComponent>());
			}

			if (entity.HasComponent<CppScriptComponent>())
			{
				SaveComponentInYaml(yamlData, entity.GetComponent<CppScriptComponent>());
			}
		yamlData << YAML::EndMap;
	}

	void Scene::SaveComponentInYaml(YAML::Emitter& yamlData, QuadComponent& component) noexcept
	{
		yamlData << YAML::Key << "quad_component";
		yamlData << YAML::Value << true;
	}

	void Scene::SaveComponentInYaml(YAML::Emitter& yamlData, TransformComponent& component) noexcept
	{
		yamlData << YAML::Key << "transform_component";
		yamlData << YAML::BeginMap;
			SaveVectorInYaml(yamlData, "position", component.position);
			SaveVectorInYaml(yamlData, "rotation", component.rotation);
			SaveVectorInYaml(yamlData, "scale", component.scale);
		yamlData << YAML::EndMap;
	}

	void Scene::SaveComponentInYaml(YAML::Emitter& yamlData, ColorComponent& component) noexcept
	{
		yamlData << YAML::Key << "color_component";
		yamlData << YAML::BeginMap;
			SaveVectorInYaml(yamlData, "color", component.color);
		yamlData << YAML::EndMap;
	}

	void Scene::SaveComponentInYaml(YAML::Emitter& yamlData, TextureComponent& component) noexcept
	{
		yamlData << YAML::Key << "texture_component";
		yamlData << YAML::BeginMap;

		yamlData << YAML::EndMap;
	}

	void Scene::SaveComponentInYaml(YAML::Emitter& yamlData, CppScriptComponent& component) noexcept
	{
		yamlData << YAML::Key << "cpp_script_component";
		yamlData << YAML::BeginMap;

		yamlData << YAML::EndMap;
	}

	void Scene::SaveComponentInYaml(YAML::Emitter& yamlData, SpriteComponent& component) noexcept
	{
		yamlData << YAML::Key << "sprite_component";
		yamlData << YAML::BeginMap;
			yamlData << YAML::Key << "texture";
			yamlData << YAML::BeginMap;
				yamlData << YAML::Key << "path";
				yamlData << YAML::Value << component.sprite->GetTexture()->GetPath();

				yamlData << YAML::Key << "coordinate";
				yamlData << YAML::Value << YAML::BeginMap;
					SaveVectorInYaml(yamlData, "left_bottom", component.sprite->GetTextureCoordinates()[0]);
					SaveVectorInYaml(yamlData, "right_bottom", component.sprite->GetTextureCoordinates()[1]);
					SaveVectorInYaml(yamlData, "right_top", component.sprite->GetTextureCoordinates()[2]);
					SaveVectorInYaml(yamlData, "left_top", component.sprite->GetTextureCoordinates()[3]);
				yamlData << YAML::Value << YAML::EndMap;
			yamlData << YAML::EndMap;
		yamlData << YAML::EndMap;
	}

	void Scene::SaveComponentInYaml(YAML::Emitter& yamlData, CameraComponent& component) noexcept
	{
		yamlData << YAML::Key << "camera_component";
		yamlData << YAML::BeginMap;
			yamlData << YAML::Key << "primary";
			yamlData << YAML::Value << component.primary;
		yamlData << YAML::EndMap;
	}

	void Scene::SaveVectorInYaml(YAML::Emitter& yamlData, const std::string& key, Math::Vector2 vector) noexcept
	{
		yamlData << YAML::Key << key;
		yamlData << YAML::BeginMap;
			yamlData << YAML::Key << "x";
			yamlData << YAML::Value << vector.x;

			yamlData << YAML::Key << "y";
			yamlData << YAML::Value << vector.y;
		yamlData << YAML::EndMap;
	}

	void Scene::SaveVectorInYaml(YAML::Emitter& yamlData, const std::string& key, Math::Vector3 vector) noexcept
	{
		yamlData << YAML::Key << key;
		yamlData << YAML::BeginMap;
			yamlData << YAML::Key << "x";
			yamlData << YAML::Value << vector.x;

			yamlData << YAML::Key << "y";
			yamlData << YAML::Value << vector.y;

			yamlData << YAML::Key << "z";
			yamlData << YAML::Value << vector.z;
		yamlData << YAML::EndMap;
	}

	void Scene::SaveVectorInYaml(YAML::Emitter& yamlData, const std::string& key, Math::Vector4 vector) noexcept
	{
		yamlData << YAML::Key << key;
		yamlData << YAML::BeginMap;
			yamlData << YAML::Key << "x";
			yamlData << YAML::Value << vector.x;

			yamlData << YAML::Key << "y";
			yamlData << YAML::Value << vector.y;

			yamlData << YAML::Key << "z";
			yamlData << YAML::Value << vector.z;

			yamlData << YAML::Key << "w";
			yamlData << YAML::Value << vector.w;
		yamlData << YAML::EndMap;
	}

}