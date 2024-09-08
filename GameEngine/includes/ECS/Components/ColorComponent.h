#pragma once

#include "Component.h"
#include "Math/Vector4.h"
#include "Core/Core.h"

namespace ECS
{

	struct GAME_ENGINE_API ColorComponent : public Component
	{
		Math::Vector4 color;
	};

}