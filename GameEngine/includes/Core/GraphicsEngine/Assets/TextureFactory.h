#pragma once

#include <string>
#include <memory>

#include "Core/Core.h"
#include "Texture.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API TextureFactory
	{
	public:
		static std::shared_ptr<Texture> Create(const unsigned int width, const unsigned int height);
		static std::shared_ptr<Texture> Create(const std::string& pathToTexture);
	};

}