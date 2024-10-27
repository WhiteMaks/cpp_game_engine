#pragma once

#include <memory>

#include "Core/Core.h"
#include "Core/GraphicsEngine/Assets/Texture.h"

namespace ECS
{

	struct GAME_ENGINE_API TextureComponent : public Component
	{
		std::shared_ptr<GraphicsEngine::Texture> texture;
	};

}