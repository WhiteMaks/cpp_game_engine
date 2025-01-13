#include "Core/GraphicsEngine/Library/Spritesheet.h"

namespace GraphicsEngine
{
	Spritesheet::Spritesheet(const std::shared_ptr<Texture>& texture, const Math::Vector2& size) noexcept
		: texture(texture), size(size)
	{
	}

	std::shared_ptr<Sprite> Spritesheet::GetSprite(const Math::Vector2& coordinate)
	{
		return GetSprite(coordinate, 0.0f);
	}

	std::shared_ptr<Sprite> Spritesheet::GetSprite(const Math::Vector2& coordinate, const float offset)
	{
		return GetSprite(coordinate, Math::Vector2(1.0f, 1.0f), offset);
	}

	std::shared_ptr<Sprite> Spritesheet::GetSprite(const Math::Vector2& coordinate, const Math::Vector2& count)
	{
		return GetSprite(coordinate, count, 0.0f);
	}

	std::shared_ptr<Sprite> Spritesheet::GetSprite(const Math::Vector2& coordinate, const Math::Vector2& count, const float offset)
	{
		const Math::Vector2 min = Math::Vector2(
			coordinate.x * size.x / texture->GetWidth(),
			coordinate.y * size.y / texture->GetHeight()
		);

		const Math::Vector2 max = Math::Vector2(
			(coordinate.x + count.x) * size.x / texture->GetWidth() - offset,
			(coordinate.y + count.y) * size.y / texture->GetHeight() - offset
		);

		return std::shared_ptr<Sprite>(new Sprite(texture, min, max));
	}
}