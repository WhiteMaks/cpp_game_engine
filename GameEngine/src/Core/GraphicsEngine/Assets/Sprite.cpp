#include "Core/GraphicsEngine/Assets/Sprite.h"

namespace GraphicsEngine
{

	Sprite::Sprite(const std::shared_ptr<Texture>& texture, const Math::Vector2& min, const Math::Vector2& max)
		: texture(texture)
	{
		textureCoordinates[0] = Math::Vector2(min.x, min.y);
		textureCoordinates[1] = Math::Vector2(max.x, min.y);
		textureCoordinates[2] = Math::Vector2(max.x, max.y);
		textureCoordinates[3] = Math::Vector2(min.x, max.y);
	}

	const std::shared_ptr<Texture> Sprite::GetTexture() const noexcept
	{
		return texture;
	}

	const Math::Vector2* Sprite::GetTextureCoordinates() const noexcept
	{
		return textureCoordinates;
	}

}