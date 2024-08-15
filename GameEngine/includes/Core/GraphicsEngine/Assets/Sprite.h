#pragma once

#include <memory>

#include "Core/Core.h"
#include "Texture.h"
#include "Tools/Math/Vector2.h"

namespace GraphicsEngine
{

	class GAME_ENGINE_API Sprite
	{
	private:
		const std::shared_ptr<Texture> texture;
	
		Math::Vector2 textureCoordinates[4];

	public: 
		Sprite(const std::shared_ptr<Texture>& texture, const Math::Vector2& min, const Math::Vector2& max);

	public: 
		const std::shared_ptr<Texture> GetTexture() const noexcept;
		const Math::Vector2* GetTextureCoordinates() const noexcept;
	};

};