#include "ECS/Systems/ColorSystem.h"

#include "Core/GraphicsEngine/Renderer/Renderer2D.h"

namespace ECS
{
	std::map<unsigned int, std::pair<std::shared_ptr<TransformComponent>, std::shared_ptr<ColorComponent>>> ECS::ColorSystem::components;


	void ColorSystem::Save(unsigned int entityId, const std::shared_ptr<TransformComponent>& transformComponent, const std::shared_ptr<ColorComponent>& colorComponent) noexcept
	{
		components[entityId] = std::make_pair(transformComponent, colorComponent);
	}

	void ColorSystem::Init() noexcept
	{
	}

	void ColorSystem::Update() noexcept
	{
	}

	void ColorSystem::Render() noexcept
	{
		for (auto& [key, value] : components)
		{
			GraphicsEngine::Renderer2D::DrawQuad(value.first->position, value.first->rotation, value.first->scale, value.second->color);
		}
	}

	void ColorSystem::Destroy() noexcept
	{
	}

}