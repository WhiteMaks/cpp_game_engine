#pragma once

#include "Component.h"
#include "Math/Vector3.h"
#include "Core/Core.h"

namespace ECS
{

	struct GAME_ENGINE_API TransformComponent : public Component
	{
		Math::Vector3 position;
		Math::Vector3 rotation;
		Math::Vector3 scale;
	};

}