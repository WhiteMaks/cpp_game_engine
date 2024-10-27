#include "ECS/Scene.h"

#include "Tools/Log.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/ColorComponent.h"
#include "ECS/Components/TextureComponent.h"
#include "ECS/Components/SpriteComponent.h"
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

	void Scene::Update() noexcept
	{
		
	}

	void Scene::Render() noexcept
	{
		RenderColorQuads();
		RenderTextureQuads();
		RenderSpriteQuads();
	}

	void Scene::Destroy() noexcept
	{
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
		auto view = registry.view<TransformComponent, ColorComponent>();
		for (auto entity : view)
		{
			auto [transformComponent, colorComponent] = view.get<TransformComponent, ColorComponent>(entity);
			GraphicsEngine::Renderer2D::DrawQuad(transformComponent.position, transformComponent.rotation, transformComponent.scale, colorComponent.color);
		}
	}

	void Scene::RenderTextureQuads() noexcept
	{
		auto view = registry.view<TransformComponent, TextureComponent>();
		for (auto entity : view)
		{
			auto [transformComponent, textureComponent] = view.get<TransformComponent, TextureComponent>(entity);
			GraphicsEngine::Renderer2D::DrawQuad(transformComponent.position, transformComponent.rotation, transformComponent.scale, textureComponent.texture);
		}
	}

	void Scene::RenderSpriteQuads() noexcept
	{
		auto view = registry.view<TransformComponent, SpriteComponent>();
		for (auto entity : view)
		{
			auto [transformComponent, spriteComponent] = view.get<TransformComponent, SpriteComponent>(entity);
			GraphicsEngine::Renderer2D::DrawSprite(transformComponent.position, transformComponent.rotation, transformComponent.scale, spriteComponent.sprite);
		}
	}

	void Scene::DestroyEntity(Entity entity) noexcept
	{
		entities.erase(entity.GetName());
		registry.destroy(entity);
	}

}