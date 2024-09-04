#pragma once

#include "Component.h"
#include "Math/Vector3.h"

namespace ECS
{

	struct TransformComponent : public Component
	{
		Math::Vector3 position;
		Math::Vector3 rotation;
		Math::Vector3 scale;
	};

}