#pragma once

#include <memory>

#include "Core/Core.h"
#include "Texture.h"
#include "Sprite.h"
#include "Tools/Math/Vector2.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API Spritesheet
	{
	private:
		const std::shared_ptr<Texture> texture;

		const Math::Vector2 size;

	public:
		Spritesheet(const std::shared_ptr<Texture>& texture, const Math::Vector2& size) noexcept;

	public:
		std::shared_ptr<Sprite> GetSprite(const Math::Vector2& coordinate);
		std::shared_ptr<Sprite> GetSprite(const Math::Vector2& coordinate, const Math::Vector2& count);
	};
}