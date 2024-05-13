#pragma once

#include <string>

#include "Core/Core.h"
#include "Texture.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API TextureFactory
	{
	public:
		static Texture* Create(const std::string& pathToTexture);
	};

}