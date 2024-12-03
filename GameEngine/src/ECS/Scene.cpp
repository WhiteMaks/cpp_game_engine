#include "ECS/Scene.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Tools/Log.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/ColorComponent.h"
#include "ECS/Components/TextureComponent.h"
#include "ECS/Components/SpriteComponent.h"
#include "ECS/Components/CameraComponent.h"
#include "ECS/Components/CppScriptComponent.h"
#include "ECS/Components/QuadComponent.h"
#include "ECS/Entity.h"
#include "Core/GraphicsEngine/Renderer/Renderer2D.h"

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

		for (const auto& [key, value] : entities)
		{
			registry.destroy(value);
		}

		entities.clear();
	}

	Entity Scene::CreateEntity(const std::string& name) noexcept
	{
		Entity result(registry.create(), this, name);

		TransformComponent& transform = result.AddComponent<TransformComponent>();
		transform.position = Math::Vector3();
		transform.rotation = Math::Vector3();
		transform.scale = Math::Vector3(1.0f);

		entities[name] = result;

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
			cppScriptComponent.instance->entity = Entity(handle, this, "Script Entity");
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

		entities.erase(entity.GetName());
		
		if (registry.valid(entity))
		{
			registry.destroy(entity);
		}
	}

}