#pragma once

#include <map>
#include <memory>

#include "System.h"

#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/ColorComponent.h"
#include "Core/Core.h"

namespace ECS
{

	class GAME_ENGINE_API ColorSystem : public System
	{
	private:
		static std::map<unsigned int, std::pair<std::shared_ptr<TransformComponent>, std::shared_ptr<ColorComponent>>> components;

	public:
		static void Save(unsigned int entityId, const std::shared_ptr<TransformComponent>& transformComponent, const std::shared_ptr<ColorComponent>& colorComponent) noexcept;

	public:
		void Init() noexcept override;
		void Update() noexcept override;
		void Render() noexcept override;
		void Destroy() noexcept override;
	};

}