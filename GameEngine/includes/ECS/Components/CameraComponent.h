#pragma once

#include "Component.h"
#include "Core/Core.h"
#include "Core/GraphicsEngine/Library/Camera.h"

namespace ECS
{

	struct GAME_ENGINE_API CameraComponent : public Component
	{
		GraphicsEngine::Camera camera;
		bool primary = true;
	};

}