#pragma once

#include <memory>

#include "Core/Core.h"
#include "Core/GraphicsEngine/Assets/Sprite.h"

namespace ECS
{

	struct GAME_ENGINE_API SpriteComponent : public Component
	{
		std::shared_ptr<GraphicsEngine::Sprite> sprite;
	};

}